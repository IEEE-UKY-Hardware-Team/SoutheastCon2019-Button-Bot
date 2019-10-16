#include <Arduino.h>
#include "../include/drive.h"

#define ENCODER_1_A 54
#define ENCODER_1_B 55
#define ENCODER_2_A 56
#define ENCODER_2_B 57

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCODER_1_A, INPUT);
  pinMode(ENCODER_1_B, INPUT);
  pinMode(ENCODER_2_A, INPUT);
  pinMode(ENCODER_2_B, INPUT);
}

const int[4] encoderPins = {ENCODER_1_A, ENCODER_1_B, ENCODER_2_A, ENCODER_2_B};
unsigned int[4] encoderCounts = {0,0,0,0};
int[4] encoderState = {LOW, LOW, LOW, LOW};


void loop() {
  // put your main code here, to run repeatedly:
  int reading = LOW;
  for (int i = 0; i < 4; i++) {
    reading = digitalRead(encoderPins[i]);
    if (reading != encoderState[i]) {
      encoderState[i] = reading;
      if (reading == HIGH) {
        encoderCounts[i]++;
      }
    }
  }
  Serial.println(encoderCounts[0]);
  Serial.println(encoderCounts[1]);
  Serial.println(encoderCounts[2]);
  Serial.println(encoderCounts[3]);
  Serial.println();
}