#include <stdlib.h>
#include <stdio.h>

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

int main(void) {
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

    // Perform quickselect algorithm
    long median = quickselect(arr, k, 0, N-1);

    // Print result
    printf("%d th element of array is %ld.\n", k, median);

    return(0);
}