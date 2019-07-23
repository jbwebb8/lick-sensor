#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include "movingFilter.h"

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
    mean = mean + (1.0 / (double) n)*(buffer[p] - bufferOld);
    
    // TODO: improve update function
    std = 0;
    for (int i = 0; i < n; i++){
        std += pow((buffer[i] - mean), 2);
    }
    std = sqrt(std / (double) n);
    //std = pow(std, 2) - (1.0 / (double) n)*(pow(bufferOld - meanOld, 2) + pow(buffer[p] - mean, 2) + 2*(buffer[p]-bufferOld)*(bufferOld-meanOld) + ((double) n - 1)/pow((double) n, 2)*pow(buffer[p]-bufferOld, 2));
    //printf("%fl\n", std);
    
    // Increment indices
    p = (p + 1) % n;
    t++;

    // Return signal
    return x;
}

int main(int argc, char *argv[]) {
    // Create new filter
    int bufferSize = atoi(argv[1]);
    double thresh = atof(argv[2]);
    double alpha = atof(argv[3]);
    MovingFilter filter(bufferSize, thresh, alpha);
    
    // Read file
    char *inFilename = argv[4];
    std::ifstream inFile(inFilename);
    printf("Reading from file %s\n", inFilename);

    // Output to file
    char *outFilename = argv[5];
    std::ofstream outFile(outFilename);
    printf("Logging to file %s\n", outFilename);

    // Stream input to filter
    if (inFile.is_open()) {
        //int x; // signal placeholder
        double y; // raw data placeholder
        
        while(inFile >> y) {
            // Output to file
            outFile << filter.applyFilter(y) << "\n";
        }
    }

    return(0);
}        
        