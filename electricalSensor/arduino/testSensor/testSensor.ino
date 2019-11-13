/*
Test sensor by turning on LED when lick detected.
*/

// Settings
int pinInput = 30; // input (connected to pull-up resistor)
int pinOutput = 24; // output (to LED)
int val = LOW;

void setup() {
    pinMode(pinInput, INPUT);
    pinMode(pinOutput, OUTPUT);
}

void loop() {
    // Input is normally pulled HIGH, switched to LOW
    // when lick completes detection circuit
    val = digitalRead(pinInput);
    digitalWrite(pinOutput, !val);
}
