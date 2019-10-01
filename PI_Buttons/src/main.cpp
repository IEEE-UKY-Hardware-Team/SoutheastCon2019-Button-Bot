#include <Arduino.h>

void activateSolenoid(int Pin) {
  // send a HIGH Signal to Pin
  digitalWrite(Pin, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i<10; i++)
  {
    pinMode(i, OUTPUT);
  }
}

bool act = true;
int pi[10] = {3,1,4,1,5, 9, 2, 6, 5, 4};
int i = 0;
unsigned long beginDelay;

void loop() {
  // put your
  // main code here, to run repeatedly:

  if(act && i < 10) {
    activateSolenoid(i);
    beginDelay = millis();
    act = false;
  } else {
    if (millis() - beginDelay < 500) {
      act = true;
      i++;
    }
  }
}