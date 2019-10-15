#include <Arduino.h>
#include "../include/drive.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  
}

const int LEFT[2] = {2,3};
int RIGHT[2] = {5,4};

int t=0;
void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  if (t < 1) {
    drive(LEFT, 125);
    drive(RIGHT, 125); 
  } else if (t < 2) {
    drive(LEFT, 0);
    drive(RIGHT, 0);
  } else if (t < 3) {
    drive(LEFT, -200);
    drive(RIGHT, -200);
  } else {
    drive(LEFT, 0);
    drive(RIGHT, 0);
  }
  t++;

}