#ifndef MOVINGFILTER_H
#define MOVINGFILTER_H

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

#endif