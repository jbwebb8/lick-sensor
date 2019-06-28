#include <CapacitiveSensor.h>

CapacitiveSensor cs = CapacitiveSensor(4, 2); // pins for capacitive sensing

int np_valve = 1; // number of pins used to drive valve
int pv[1] = {23}; // which pins are the actual pins?
int pulseWidth = 100; // duration of digital pulse (ms)

byte lick = 0; // lick variable
long th = 100; // threshold for detecting lick
float sampleRate = 30000.0; // rate to print to serial
unsigned long tStart;
unsigned long tCurrent; 
unsigned long samplePeriod; 

int ledVoltage = LOW;

void setup() {
  
  // Set pins to low voltage
  for (int i = 0; i < np_valve; i++)
  {
    pinMode(pv[i], OUTPUT);
    digitalWrite(pv[i], LOW);
  }

  // Begin serial transmission
  Serial.begin(115200);
  
  // Get start time and minimum sample period
  tStart = micros(); // time in ms
  samplePeriod = (unsigned long) ((1.0/sampleRate)*10e6); // period in us
}

void loop() {
  // Get current sensor value and time
  // Note: sensor value acquisition limits transmission rate
  long val = cs.capacitiveSensor(30); // sensitivity
  tCurrent = micros();

  // Write sensor value with sample frequency or if clock restarted
  if ((tCurrent - tStart > samplePeriod) || (tCurrent - tStart < 0))
  {
    Serial.print(tCurrent);
    Serial.print(" ");
    Serial.print(val);
    Serial.print("\n");
    tStart = tCurrent;
  }
  
  // Write digital I/O if threshold crossed
  if ((val > th) && (ledVoltage == LOW))
  {
    writePins(HIGH);
    ledVoltage = HIGH;
  }
  else if ((val < th) && (ledVoltage == HIGH))
  {
    writePins(LOW);
    ledVoltage = LOW;
  }
}

void writePins(uint8_t mode)
{
  for (int i = 0; i < np_valve; i++)
  {
    digitalWrite(pv[i], mode);
  }
}
