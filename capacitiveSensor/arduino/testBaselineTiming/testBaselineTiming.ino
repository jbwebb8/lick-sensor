#include <CapacitiveSensor.h>

// Settings
int nSensors = 1; // number of lick sensors
int sensitivity = 30; // number of samples per sensor read
long th = 200; // threshold for detecting lick
float sampleRate = 30000.0; // rate to print to serial

// Sensor I/O
CapacitiveSensor cs[] = {
  //CapacitiveSensor(4, 2), // pins for capacitive sensing
  CapacitiveSensor(13, 11)
};
long vals[1]; // sensor values
int pinsOut[1] = {23}; // output pins
int output[1] = {LOW}; // current output states

// Timing variables
unsigned long tStart;
unsigned long tCurrent; 
unsigned long samplePeriod;

// Drift correction
long baselineStart; // old baseline
long baselineCurrent; // current baseline
long valsBuffer[]; // previous x sensor values
int bufferPointer; // current buffer position

void setup() {
  // Set pins to low voltage
  for (int i = 0; i < nSensors; i++)
  {
    pinMode(pinsOut[i], OUTPUT);
    digitalWrite(pinsOut[i], LOW);
  }

  // Begin serial transmission
  Serial.begin(115200);
  
  // Get start time and minimum sample period
  tStart = micros(); // time in ms
  samplePeriod = (unsigned long) ((1.0/sampleRate)*10e6); // period in us

  // Set sensor value buffer
  valsBuffer[10];
}

void loop() {
  // Get current sensor value and time
  // Note: sensor value acquisition limits transmission rate
  for (int i = 0; i < nSensors; i++)
  {
    vals[i] = cs[i].capacitiveSensor(sensitivity);
  }
  tCurrent = micros();

  // Calculate baseline every x ms
  valsBuffer[bufferPointer] = vals[0];


  // Write sensor value with sample frequency or if clock restarted
  if ((tCurrent - tStart > samplePeriod) || (tCurrent - tStart < 0))
  {
    Serial.print(tCurrent);
    for (int i = 0; i < nSensors; i++)
    {
      Serial.print(" ");
      Serial.print(vals[i]);
    }
    Serial.print("\n");
    tStart = tCurrent;
  }
  
  // Write digital I/O if threshold crossed
  for (int i = 0; i < nSensors; i++)
  {
    if ((vals[i] > th) && (output[i] == LOW))
    {
      digitalWrite(pinsOut[i], HIGH);
      output[i] = HIGH;
    }
    else if ((vals[i] < th) && (output[i] == HIGH))
    {
      digitalWrite(pinsOut[i], LOW);
      output[i] = LOW;
    }
  }
}


