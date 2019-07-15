#include <CapacitiveSensor.h>

// Settings
int nSensors = 1; // number of lick sensors
long th = 100; // threshold for detecting lick
float sampleRate = 30000.0; // rate to print to serial
float pulse = 0.200; // pulse length (s)

// Sensor I/O (constructor format: (pinSend, pinReceive))
CapacitiveSensor cs[] = {
    CapacitiveSensor(4, 2) 
};
long vals[1]; // sensor values
int pinsOut[1] = {22}; // output pins
int output[1] = {LOW}; // current output states

// Timing variables
unsigned long tStart;
unsigned long tCurrent; 
unsigned long samplePeriod;
unsigned long pulseLength; // length of pulse (us)
unsigned long pulseStart[1]; // length of current pulse (s)
bool isLickFinished; // tracks falling edge of sensor

void setup() {
    // Set pins to low voltage
    for (int i = 0; i < nSensors; i++) {
        pinMode(pinsOut[i], OUTPUT);
        digitalWrite(pinsOut[i], LOW);
    }

    // Begin serial transmission
    Serial.begin(115200);
    
    // Get start time and minimum sample period
    tStart = micros(); // time in ms
    samplePeriod = (unsigned long) ((1.0/sampleRate)*10e6); // period in us
    
    // Initialize pulse variables
    pulseLength = (unsigned long) pulse*10e6; // convert to us
    for (int i = 0; i < nSensors; i++) {
        pulseStart[i] = 0;
    }
    isLickFinished = false;
}

void loop() {
    // Get current sensor value and time
    // Note: sensor value acquisition limits transmission rate
    for (int i = 0; i < nSensors; i++) {
        vals[i] = cs[i].capacitiveSensor(30);
    }
    tCurrent = micros();

    // Write sensor value with sample frequency or if clock restarted
    if ((tCurrent - tStart > samplePeriod) || (tCurrent - tStart < 0)) {
        Serial.print(tCurrent);
        for (int i = 0; i < nSensors; i++) {
            Serial.print(" ");
            Serial.print(vals[i]);
        }
        Serial.print("\n");
        tStart = tCurrent;
    }
    
    // Write digital I/O if threshold crossed
    for (int i = 0; i < nSensors; i++) {
        // Begin reward pulse if:
        // 1) sensor detection threshold crossed,
        // 2) output is LOW, and
        // 3) previous lick finished.
        if ((vals[i] > th) && (output[i] == LOW) && (isLickFinished)) {
            digitalWrite(pinsOut[i], HIGH);
            output[i] = HIGH;
            pulseStart[i] = tCurrent;
            isLickFinished = false;
        }
        // Stop reward pulse if:
        // 1) currently dispensing reward, and
        // 2) pulse width reached.
        else if ((output[i] == HIGH) && (tCurrent - pulseStart[i] > pulse)) {
            digitalWrite(pinsOut[i], LOW);
            output[i] = LOW;
        }
        // Lick is finished if: 
        // 1) sensor detection threshold crossed, and 
        // 2) lick was occurring.
        else if ((vals[i] < th) && (!isLickFinished)) {
            isLickFinished = true;
        }
    }
}
