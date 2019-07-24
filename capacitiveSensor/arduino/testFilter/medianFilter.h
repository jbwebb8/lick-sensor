#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

// Get random integer in [lower, upper]
// Credit: https://www.geeksforgeeks.org/generating-random-number-range-c/
int randomInt(int lower, int upper);

// Swap two elements of an array
template <class T>
void swap(T *xp, T *yp);

// Group subarray into two smaller subarrays (< pivotValue, >= pivotValue),
// returning the index of the partition. Uses Lomuto partition scheme, 
// which is simpler but less efficient than Hoare's original partition scheme.
template <class T>
int partition(T arr[], int pivotIndex, int left, int right);

// Select k-th greatest element in sorted array within bounds [left, right]
template <class T>
T quickselect(T arr[], int k, int left, int right);

#endif