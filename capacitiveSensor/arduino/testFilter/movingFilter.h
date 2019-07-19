class MovingFilter {

    private:
        int t; // current sample number
        int p; // current pointer in buffer
        float mean; // current buffer mean
        float std; // current buffer std
        float *buffer; // buffer containing filter applied to last n data points

    public:
        // Filter parameters
        int n; // length of buffer in data points
        float thresh; // number of stds from mean that constitutes signal
        float alpha; // influence of most recent data point containing signal
        
        // Constructor
        MovingFilter(int n, float thresh, float alpha);

        // Destructor
        ~MovingFilter();

        // Methods
        int applyFilter(float y);
};
