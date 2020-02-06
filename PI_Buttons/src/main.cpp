#include <Arduino.h>
#include "../include/pi10000.h"
#include "drive.h"
// #include "Arduino_LCD.h"
#include <Servo.h>

#define digit_00          2
#define digit_01          3
#define digit_02          4
#define servo_1           5 //#define digit_03          5
#define servo_2           6 //#define digit_04          6
#define digit_05          7
#define digit_06          8
#define digit_07          9
#define digit_08          12
#define digit_09          13
#define drive_pin_a       10
#define drive_pin_b       11
#define trigger_pin       A0
#define release_arms_pin  A1
#define drive_forward     255
#define digit_03          A2
#define digit_04          A3

#define hook_start_angle 0
#define hook_down_angle 179

//Defining servo objects?
Servo hook_servo_1;
Servo hook_servo_2;

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
  //Serial.begin(9600);
  pinMode(digit_00, OUTPUT);
  pinMode(digit_01, OUTPUT);
  pinMode(digit_02, OUTPUT);
  pinMode(digit_03, OUTPUT);
  pinMode(digit_04, OUTPUT);
  pinMode(digit_05, OUTPUT);
  pinMode(digit_06, OUTPUT);
  pinMode(digit_07, OUTPUT);
  pinMode(digit_08, OUTPUT);
  pinMode(digit_09, OUTPUT);
  pinMode(trigger_pin, INPUT_PULLUP);
  pinMode(release_arms_pin, OUTPUT);
  pinMode(drive_pin_a, OUTPUT);
  pinMode(drive_pin_b, OUTPUT);
  
  //pinMode(servo_1, OUTPUT);
  //pinMode(servo_2, OUTPUT);

  hook_servo_1.attach(servo_1);
  hook_servo_2.attach(servo_2);
  
  // write hook servos to start position
  hook_servo_1.write(hook_start_angle);
  hook_servo_2.write(hook_start_angle);
}
// Figure out which pins could be used as pwm for arduino pro mini
// Designate those as for the servos in #define.
//**********************************************
// Pins 5 & 6 used for Servos 1 and 2 respetively
//**********************************************

// Replace whatever solenoids was using them so that they can use analog.
//**********************************************
// Solenoids moved to A2 and A3
//**********************************************

// Write code so that as the robot drives forward, the servos will rotate 90 degrees.
//**********************************************
// pending...
//**********************************************


const unsigned long SPACING = 75;  // ms between presses
const unsigned long DURATION = 75; // duration of a press

bool act = true; // if act is true some solenoid needs to toggle
bool extended = false; // if extended is true one solenoid is extended
int piIndex = 0; 
unsigned long beginDelay;
int pinNumber = 0;
bool startPressed = false;
bool atWall = false;
int drivePins[2] = {drive_pin_a, drive_pin_b};

void loop() {

  while (!startPressed) {
    if(analogRead(trigger_pin) > 122) {
      startPressed = true;
      delay(1000);
      //drop hook servos
      hook_servo_1.write(hook_down_angle);
      hook_servo_2.write(hook_down_angle);
    }
  }
  // IDEA: put start button in parrallel with two trigger buttons.
  // drive forward until both switches hit.
  
  while (!atWall) {
    drive(drivePins, drive_forward);
    if (analogRead(trigger_pin) > 122) {
      atWall = true;
      delay(200);
      brake(drive_pin_a, drive_pin_b);
      deactivateSolenoid(release_arms_pin);
    }
  }

  if(act) {
    pinNumber = pgm_read_byte_near(bigPI + piIndex);
    

    //Serial.println(piIndex);
    //Serial.println(pinNumber - '0');
    switch(pinNumber)
    {
      case '0':
        pinNumber = digit_00;
        break;
      case '1':
        pinNumber = digit_01;
        break;
      case '2':
        pinNumber = digit_02;
        break;
      case '3':
        pinNumber = digit_03;
        break;
      case '4':
        pinNumber = digit_04;
        break;
      case '5':
        pinNumber = digit_05;
        break;
      case '6':
        pinNumber = digit_06;
        break;
      case '7':
        pinNumber = digit_07;
        break;
      case '8':
        pinNumber = digit_08;
        break;
      case '9':
        pinNumber = digit_09;
        break;
      default:
        pinNumber = digit_00;
    }
    //If statements to toggle between extend/retract
    if (extended) {
      deactivateSolenoid( pinNumber );
      extended = false;
      //Serial.print("deactivate ");
      //Serial.println(pinNumber );
    } else {
      activateSolenoid( pinNumber );
      extended = true;
      //Serial.print("activate ");
      //Serial.println( pinNumber );
    }

    beginDelay = millis();
    act = false;
  } 
  else 
  {
    if (millis() - beginDelay > (extended ? DURATION : SPACING))
      {
        act = true;
        if (!extended) 
        {
          // only iterate pi index when we have extended and unextended
          piIndex++;
        }
      }
  }

}

