#ifndef FILTER_H
#define FILTER_H

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

class MovingFilter {

    private:
        int t; // current sample number
        int p; // current pointer in buffer
        double mean; // current buffer mean
        double std; // current buffer std
        double *buffer; // buffer containing filter applied to last n data points

    public:
        // Filter parameters
        int n; // length of buffer in data points
        double thresh; // number of stds from mean that constitutes signal
        double alpha; // influence of most recent data point containing signal
        
        // Constructor
        MovingFilter(int n, double thresh, double alpha);

        // Destructor
        ~MovingFilter() {};

        // Methods
        int applyFilter(double y);
};

// Necessary to link implementation of template classes and methods. 
// See here: https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
#include "filter.cpp"

#endif