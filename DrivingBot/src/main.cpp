#include <Arduino.h>
#include "../include/drive.h"

//These are all the interrrupt pins for the Mega, Mega2560 and MegaADK
#define Mega2560_interupt_pin_1 2
#define Mega2560_interupt_pin_2 3
#define Mega2560_interupt_pin_3 18
#define Mega2560_interupt_pin_4 19
#define Mega2560_interupt_pin_5 20
#define Mega2560_interupt_pin_6 21

//These are the interrurt pins for the Uno, Nano, Mini and other
//328-based microcontrollers
#define Uno_interupt_pin_1 2
#define Uno_interupt_pin_2 3


#define digital_pin_A  8
#define digital_pin_B  7
#define digital_pin_C  6
#define digital_pin_D  5

int count = 0, lastA = 0, currentA = 0;
int wheel_rotation_count = 0;
unsigned long lastSampleClock = 0;
unsigned long currClock = 0;
int drivePins[2] = {digital_pin_C, digital_pin_D};



PID pid1(0.9, 0.0001, 0);


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

  //attach interrupt intiializes an interrupt pin. attachInterrupt(digitalPinToInterrupt(pin_number),ISR,mode)
  //digitalPinTointerrupt sets the interrupt pin, 
  //encoder_count_rising is the Interrupt Sub-Routine (ISR)  
  //RISING is the mode(calls ISR on rising edge of pin)
  attachInterrupt(digitalPinToInterrupt(Mega2560_interupt_pin_1), encoder_count_rising, RISING);

  lastSampleClock = 0;

  // drive(drivePins, motor_slowest);
}

void loop() {
  // put your main code here, to run repeatedly:
  currClock = micros();
  currentA = digitalRead(digital_pin_A);
  //if (lastA != currentA && lastA == 0)
  //{
    //if (digitalRead(digital_pin_B)) {
      //count++;
    //} else {
    //  count--;
    //}
    // Serial.println(count);
  //}
  // Serial.println(digitalRead(digital_pin_A));
  //Serial.println(count);
  lastA = currentA;

  //Serial.print("Clock");  
  //Serial.println(currClock - lastSampleClock);

  if (currClock - lastSampleClock > 1000) {
    int error = 360 - count;
    drive(drivePins, pid1.evaluate(error));
    //Serial.print("error");
    Serial.println(error);
    lastSampleClock = currClock;
  }
}

//This is the Interupt Sub-Routine (ISR)
void encoder_count_rising()
{
  count++;
}