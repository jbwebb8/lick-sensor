#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

// Get random integer in [lower, upper]
// Credit: https://www.geeksforgeeks.org/generating-random-number-range-c/
int randomInt(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

// Swap two elements of an array
void swap(long *xp, long *yp) {
    // Remember: * = get value of pointer
    //           & = get pointer of value
    long t = *xp;
    *xp = *yp;
    *yp = t;
}

// Group subarray into two smaller subarrays (< pivotValue, >= pivotValue),
// returning the index of the partition. Uses Lomuto partition scheme, 
// which is simpler but less efficient than Hoare's original partition scheme.
int partition(long arr[], int pivotIndex, int left, int right) {
    // Get value of arr[pivotIndex]
    long pivotValue = arr[pivotIndex];

    // Move pivot to end
    swap(&arr[pivotIndex], &arr[right]);

    // Place all subarray elements < pivotValue on left side of subarray
    int idx = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(&arr[idx], &arr[i]);
            idx++;
        }
    }

    // Move pivot from end to proper place, splitting two new subarrays
    swap(&arr[idx], &arr[right]);

    return idx;
}

long quickselect(long arr[], int k, int left, int right) {
    // Return element if size(subarray) = 1
    if (left == right) {
        return arr[left];
    }
    
    // Select random pivot (can use median-of-medians for faster time)
    int pivotIndex = randomInt(left, right);

    // Find sorted index of arr[pivotIndex]
    pivotIndex  = partition(arr, pivotIndex, left , right);

    // Further subpartition if needed
    if (k == pivotIndex) {
        // Return element if pivotIndex = k
        return arr[k];
    }
    else if (k < pivotIndex) {
        // Search in left side of array if k > pivotIndex
        return quickselect(arr, k, left, pivotIndex-1);
    }
    else {
        // Search in right side of array if k > pivotIndex
        return quickselect(arr, k, pivotIndex+1, right);
    }
}

int main(int argc, char *argv[]) {
    /*
    // NOTE: In C, arrays are passed as pointers, so size information is lost.
    // If another function needs array size information, it must be passed as
    // a separate parameter.
    long arr[] = {7, 5, 2, 3, 4, 1, 9, 6, 3, 5, 6};
    int k;
    char buf[8];
    
    // Get array size
    int N = sizeof(arr) / sizeof(arr[0]);

    // Get k from stdin
    printf ("Enter your number: ");
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        k = atoi(buf);
    }
    else {
        k = (int) sizeof(arr) / sizeof(arr[0]) / 2;
    }
    */

    // Get command line arguments
    int N = atoi(argv[1]); // length of array
    int k = atoi(argv[2]); // k-th median
    int M = atoi(argv[3]); // number of iterations

    // Create random array
    long arr[N];
    srand(time(NULL));
    for (int n = 0; n < N; n++) {
        arr[n] = rand();
    }

    // Time loops
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int m = 0; m < M; m++) {
        // Perform quickselect algorithm
        long median = quickselect(arr, k, 0, N-1);

        // Print result
        //printf("%d th element of array is %ld.\n", k, median);
    }
    gettimeofday(&end, NULL);
    double tTotal = ((double) (end.tv_sec - start.tv_sec)) + 10e-6*((double) (end.tv_usec - start.tv_usec));
    double tLoop = tTotal / (double) M;
    printf("Total time: %lf s (%lf s per loop)\n", tTotal, tLoop);

    // Exit
    return(0);
}