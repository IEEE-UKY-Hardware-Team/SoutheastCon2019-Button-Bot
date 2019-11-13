#include <Arduino.h>
#include "../include/drive.h"

int digital_pin_A = 8;
int digital_pin_B = 7;
int digital_pin_C = 6;
int digital_pin_D = 5;
int count = 0, last = 0, current = 0;
int wheel_rotation_count = 0;
unsigned long lastSampleClock = 0;
unsigned long currClock = 0;
int drivePins[2] = {digital_pin_C, digital_pin_D};

PID pid1(0.4, 0, 0);

#define motor_slowest 45
#define motor_fastest 255

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(digital_pin_A,INPUT);
  pinMode(digital_pin_B,INPUT);
  pinMode(digital_pin_C,OUTPUT);
  pinMode(digital_pin_D,OUTPUT);

  analogWrite(digital_pin_C, 0);
  analogWrite(digital_pin_D, motor_slowest);
  lastSampleClock = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  currClock = micros();
  current = digitalRead(digital_pin_A);
  if (last != current && last == 0)
  {
    count++;
  }
  //Serial.println(digitalRead(digital_pin_A));
  last = current;


  //Serial.print("Clock");  
  //Serial.println(currClock - lastSampleClock);

  if (currClock - lastSampleClock > 1000) {
    int error = -(360 - count);
    drive(drivePins, pid1.evaluate(error));
    //Serial.print("error");
    //Serial.println(error);
    count = 0;
    lastSampleClock = currClock;
  }
}
