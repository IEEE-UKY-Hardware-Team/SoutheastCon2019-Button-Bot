#include <Arduino.h>
// #include "../include/drive.h"
#include "../include/ultrasonic.h"
#include "./encoderMain.h"
#include "./PI_Buttons.h"

const int trigPin = 9;
const int echoPin = 10; 

void setup() {
  // put your setup code here, to run once:
  // ultrasonicSetup(trigPin, echoPin);
  PISolenoidSetup();
  
}

const int LEFT[2] = {2,3};
int RIGHT[2] = {5,4};

int t=0;
void loop() {
  // put your main code here, to run repeatedly:
  // ultrasonicLoop(trigPin, echoPin);
  PISolenoidLoop();
  

}