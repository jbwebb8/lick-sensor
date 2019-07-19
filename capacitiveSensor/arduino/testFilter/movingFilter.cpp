#include<stdlib.h>
#include<stdio.h>
#include<movingFilter.h>

// Filter constructor
movingFilter::movingFilter(int n, float thresh, float alpha) {
    // Set parameters
    this->n = n;
    this->thresh = thresh;
    this->alpha = alpha;

    // Set variables
    t = 0;
    p = 0;
    mean = 0.0;
    std = 0.0;

    buffer = new float[n]; // allocate buffer
}

// Filter methods
int movingFilter::applyFilter(float y) { 
    // Signal value
    int x;
    float bufferNext;

    // Check if buffer filled
    if (t > n) {
        // Check if signal threshold crossed
        if (abs(y - mean) > (thresh*std)) {
            // Update signal array
            if ((y - mean) > 0.0) { // positve signal
                x = 1;
            }
            else { // negative signal
                x = -1;
            }

            // Update buffer
            bufferNext = (alpha*y) + ((1.0 - alpha)*y
            
        }

        // Update buffer stats
        mean = mean - (1/n)*buffer[p] + (1/n);
        buffer[p] = y;
    }
    else {

    }
}
            
            
        