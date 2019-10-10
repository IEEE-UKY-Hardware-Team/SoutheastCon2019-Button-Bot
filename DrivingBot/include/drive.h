#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTIONS

#include <Arduino.h>

// Each motor is driven by two pins.
// The first pin in the pins array controls forward speed
// the second pin conrols backward speed for the same motor
// if {255, 255} then the motor brakes
// if {0, 0} then the motor coasts
// if {255, 0} the motor goes forward at full power
// if {0, 255} the motor goes backward at full power

// At the moment the values we can pass in only range from 0 to 255. we need more values!

void brake(int pin1, int pin2)
{
    analogWrite(pin1, 255);
    analogWrite(pin2, 255);
}

void drive(const int pins[2], int value)
{
    // the pins array holds the two pins that control a motor.
    // I can imagine expanding this function to "duplicate" the controls to any number of motors
    //  ie: write a loop that repeats the interior of the ifs for pins[i] and pins[i+1]

    if (value < 0)
    {
        analogWrite(pins[0], 0);
        analogWrite(pins[1], value * -1);
    }
    else if (value == 0)
    {
        analogWrite(pins[0], 0);
        analogWrite(pins[1], 0);
    }
    else
    {
        analogWrite(pins[0], value);
        analogWrite(pins[1], 0);
    }
}

void both(const int left[2], const int right[2], int value)
{
    drive(left, value);
    drive(right, value);
}

int PID(int error, float P, float I, float D)
{
    // K = P*error(t) + (I*integral_0-->t) (error(T)) dT  D*(d/dt(error(t)))
    // maximum error is P * 255

    return P * error;
}

#endif