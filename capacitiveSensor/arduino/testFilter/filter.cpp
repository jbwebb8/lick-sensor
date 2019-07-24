#include <stdlib.h>
#include <cmath>
#include "filter.h"

/* median (quickselect) methods */

// Get random integer in [lower, upper]
// Credit: https://www.geeksforgeeks.org/generating-random-number-range-c/
int randomInt(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

// Swap two elements of an array
template <class T>
void swap(T *xp, T *yp) {
    // Remember: * = get value of pointer
    //           & = get pointer of value
    T t = *xp;
    *xp = *yp;
    *yp = t;
}

// Group subarray into two smaller subarrays (< pivotValue, >= pivotValue),
// returning the index of the partition. Uses Lomuto partition scheme, 
// which is simpler but less efficient than Hoare's original partition scheme.
template <class T>
int partition(T arr[], int pivotIndex, int left, int right) {
    // Get value of arr[pivotIndex]
    T pivotValue = arr[pivotIndex];

    // Move pivot to end
    swap<T>(&arr[pivotIndex], &arr[right]);

    // Place all subarray elements < pivotValue on left side of subarray
    int idx = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap<T>(&arr[idx], &arr[i]);
            idx++;
        }
    }

    // Move pivot from end to proper place, splitting two new subarrays
    swap<T>(&arr[idx], &arr[right]);

    return idx;
}

// Select k-th greatest element in sorted array within bounds [left, right]
template <class T>
T quickselect(T arr[], int k, int left, int right) {
    // Return element if size(subarray) = 1
    if (left == right) {
        return arr[left];
    }
    
    // Select random pivot (can use median-of-medians for faster time)
    int pivotIndex = randomInt(left, right);

    // Find sorted index of arr[pivotIndex]
    pivotIndex  = partition<T>(arr, pivotIndex, left , right);

    // Further subpartition if needed
    if (k == pivotIndex) {
        // Return element if pivotIndex = k
        return arr[k];
    }
    else if (k < pivotIndex) {
        // Search in left side of array if k > pivotIndex
        return quickselect<T>(arr, k, left, pivotIndex-1);
    }
    else {
        // Search in right side of array if k > pivotIndex
        return quickselect<T>(arr, k, pivotIndex+1, right);
    }
}

/* moving filter class */

// Filter constructor
MovingFilter::MovingFilter(int n, double thresh, double alpha) {
    // Set parameters
    this->n = n;
    this->thresh = thresh;
    this->alpha = alpha;

    // Set variables
    t = 0;
    p = 0;
    mean = 0.0;
    std = 0.0;

    // Allocate buffer
    buffer = new double[n];
}

// Filter methods
int MovingFilter::applyFilter(double y) { 
    // Signal value
    int x;
    
    // Cache old value
    double bufferOld = buffer[p];
    double meanOld = mean;

    // Check for signal (if buffer filled)
    if ((t > n) && (abs(y - mean) > (thresh*std))) {
        // Update signal array
        if ((y - mean) > 0.0) { // positve signal
            x = 1;
        }
        else { // negative signal
            x = -1;
        }

        // Update buffer
        int prev = ((p - 1) + n) % n; // wraps to end if needed
        buffer[p] = (alpha*y) + ((1.0 - alpha)*buffer[prev]);
    }
    else {
        // Update signal and buffer
        x = 0;
        buffer[p] = y;
    }

    // Update buffer stats
    if (t % 100 == 0) {
        // Get ground truth stats occasionally to correct drift
        mean = 0;
        for (int i = 0; i < n; i++) {
            mean += buffer[i];
        }
        mean = mean / (double) n;
        std = 0;
        for (int i = 0; i < n; i++){
            std += pow((buffer[i] - mean), 2);
        }
        std = sqrt(std / (double) n);
    }
    else {
        // Use single point updates for faster processing
        double dMean = (1.0/(double) n)*(buffer[p] - bufferOld);
        mean += dMean;
        std = (pow(std, 2) - (1.0/(double) n)*pow(bufferOld - meanOld, 2) 
               + (1.0/(double) n)*pow(buffer[p] - mean, 2) 
               + (2*dMean/(double) n)*(bufferOld - meanOld) 
               + (((double) n - 1)/((double) n))*pow(dMean, 2));
        std = sqrt(std);
    }

    // Increment indices
    p = (p + 1) % n;
    t++;

    // Return signal
    return x;
}