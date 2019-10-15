#ifndef ULTRASONIC
#define ULTRASONIC

#include <Arduino.h>

long duration;
int distanceIN;
int distanceCM;

void ultrasonicSetup(int trigPin, int echoPin) {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void ultrasonicLoop(int trigPin, int echoPin) {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceCM = duration * (0.034 / 2);
  distanceIN = distanceCM / 2.54;

  //Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  //Serial.print("Distance in in: ");
  //Serial.println(distanceIN);
}

#endif