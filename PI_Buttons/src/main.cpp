#include <Arduino.h>

void activateSolenoid(int Pin) {
  // send a HIGH Signal to Pin
  digitalWrite(Pin, HIGH);
}

void deactivateSolenoid(int Pin) {
  // send a HIGH Signal to Pin
  digitalWrite(Pin, LOW);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i<10; i++)
  {
    pinMode(i, OUTPUT);
  }
}

const unsigned long SPACING = 500;  // ms between presses
const unsigned long DURATION = 300; // duration of a press
const char pi[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 4};

bool act = true; // if act is true some solenoid needs to toggle
bool extended = false; // if extended is true one solenoid is extended
int pi_index = 0; 
unsigned long beginDelay;

void loop() {

  if(act) {
    if (extended) {
      deactivateSolenoid(pi[pi_index]);
      extended = false;
    } else {
      activateSolenoid(pi[pi_index]);
      extended = true;
    }

    beginDelay = millis();
    act = false;
  } else {
    if (millis() - beginDelay < (extended ? DURATION : SPACING)) {
      act = true;
      if (!extended) {
        // only iterate pi index when we have extended and unextended
        pi_index++;
      }
    }
  }

  // put your main code here, to run repeatedly:
}
