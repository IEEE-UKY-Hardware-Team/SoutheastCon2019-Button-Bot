#include <Arduino.h>
#include "../include/drive.h"

int digital_pin_A = 8;
int digital_pin_B = 7;
int digital_pin_C = 6;
int digital_pin_D = 5;
int count = 0, lastA = 0, currentA = 0;
int wheel_rotation_count = 0;
unsigned long lastSampleClock = 0;
unsigned long currClock = 0;
int drivePins[2] = {digital_pin_C, digital_pin_D};

PID pid1(0.5, 0.001, 0);


#define motor_slowest 45
#define motor_fastest 255

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pid1.SetFrequency(1000);
  pinMode(digital_pin_A,INPUT);
  pinMode(digital_pin_B,INPUT);
  pinMode(digital_pin_C,OUTPUT);
  pinMode(digital_pin_D,OUTPUT);
  lastSampleClock = 0;

  // drive(drivePins, motor_slowest);
}

void loop() {
  // put your main code here, to run repeatedly:
  currClock = micros();
  currentA = digitalRead(digital_pin_A);
  if (lastA != currentA && lastA == 0)
  {
    if (digitalRead(digital_pin_B)) {
      count++;
    } else {
      count--;
    }
    // Serial.println(count);
  }
  // Serial.println(digitalRead(digital_pin_A));
  // Serial.println(count);
  lastA = currentA;

  //Serial.print("Clock");  
  //Serial.println(currClock - lastSampleClock);

  if (currClock - lastSampleClock > 1000) {
    int error = 360 - count;
    // drive(drivePins, pid1.evaluate(error));
    // Serial.print("error");
    Serial.println(error);
    lastSampleClock = currClock;
  }
}
