#include <Arduino.h>
#include "../include/pi10000.h"
// #include "Arduino_LCD.h"

void activateSolenoid(int Pin) {
  // send a HIGH Signal to Pin
  digitalWrite(Pin, HIGH);
}

void deactivateSolenoid(int Pin) {
  // send a HIGH Signal to Pin
  digitalWrite(Pin, LOW);
}

int pinOffset = 2;

void PISolenoidSetup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  for (int i = pinOffset; i < (10+pinOffset); i++)
  {
    pinMode(i, OUTPUT);
  }
}

const unsigned long SPACING = 40;  // ms between presses
const unsigned long DURATION = 40; // duration of a press

bool act = true; // if act is true some solenoid needs to toggle
bool extended = false; // if extended is true one solenoid is extended
int piIndex = 0; 
unsigned long beginDelay;

void PISolenoidLoop() {

  if(act) {
    int pinNumber = bigPI[piIndex] - '0';
    if (extended) {
      deactivateSolenoid( pinNumber + pinOffset );
      extended = false;
      Serial.print("deactivate ");
      Serial.println(pinNumber + pinOffset);
    } else {
      activateSolenoid( pinNumber + pinOffset );
      extended = true;
      Serial.print("activate ");
      Serial.println(pinNumber + pinOffset);
    }

    beginDelay = millis();
    act = false;
  } else {
    if (millis() - beginDelay > (extended ? DURATION : SPACING)) {
      act = true;
      if (!extended) {
        // only iterate pi index when we have extended and unextended
        piIndex++;
      }
    }
  }

  // put your main code here, to run repeatedly:
}
