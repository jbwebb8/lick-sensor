int len = 
long arr[100];
void setup() {

}

void loop() {
    // send data only when you receive data:
    if (Serial.available() > 0) {
        
}


long median(long[] arr) {

}

void bubblesort(long[] arr) {
    // Get array size
    n = sizeof(arr) / sizeof(arr[0]);

    // Iterate through array
    bool isSorted;
    for (i = 0; i < n; i++) {
        isSorted = true;
        for (j = i; j < n; j++) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j])
                isSorted = false;
            }
        }
        if (isSorted) {
            break;
        }
    }
}

void swap(long *xp, long *yp) {
    long t = *xp;
    *xp = *yp;
    *yp = t;
}