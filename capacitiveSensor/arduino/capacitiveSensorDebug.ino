#include <CapacitiveSensor.h>

CapacitiveSensor cs = CapacitiveSensor(4, 2); // pins for capacitive sensing

int np_valve = 1; // number of pins used to drive valve
int pv[1] = {23}; // which pins are the actual pins?
int pulseWidth = 100; // duration of digital pulse (ms)

byte lick = 0; // lick variable
long th = 100; // threshold for detecting lick
int updateTime = 100; // print values every x ms
long tStart;

int ledVoltage = LOW;

void setup() {
  
  // Set pins to low voltage
  for (int i = 0; i < np_valve; i++)
  {
    pinMode(pv[i], OUTPUT);
    digitalWrite(pv[i], LOW);
  }
  Serial.begin(115200);
  
  tStart = millis(); // time in ms
}

void loop() {
  long val = cs.capacitiveSensor(30); // sensitivity
  long tCurrent = millis();
  
  if (tCurrent - tStart > updateTime)
  {
    Serial.print(val);
    Serial.print("\t");
    tStart = tCurrent;
  }
  
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

  lick = lick || (val > th); // accumulate licks

  if (Serial.available() > 0)
  {
    int cmd = Serial.read(); // read command
    Serial.print(cmd);
    Serial.print("\t");
    
    switch (cmd)
    {
      // Start monitoring for licks
      case 0:
        lick = 0;
        break;

      // Stop monitoring for licks
      case 1:
        Serial.write(lick);
        break;

      // Deliver reward
      case 2:
        Serial.print("Delivering reward...");
        writePins(HIGH);
        delay(pulseWidth);
        writePins(LOW);
        break;

      // New value for pulse width
      default:
        pulseWidth = cmd;
        break;
    }
  }
}

void writePins(uint8_t mode)
{
  for (int i = 0; i < np_valve; i++)
  {
    digitalWrite(pv[i], mode);
  }
}