#pragma once

#include <Arduino.h>

/* 
 * This class will be able to grab position and velocity from an encoder.
 * Position:
 *  I ask very frequently (scale of MegaHertz) if the reading on pinA has changed from low to high
 *      if so, we need to determine the direction with the polarity of the other pin.
 *          If we're moving forward, add a tick to the position, or subtract one for backwards motion.
 *          "forward is relative and nothing makes sense"
 *
 * Velocity:
 *  
 *
 */

const int BUFFER_SIZE = 50;

class encoder {
    public:
        encoder(int digital_pin_A, int digital_pin_B);
        void evaluate(); 
        int getPosition();
        float getSpeed(); 
        void zeroPosition();
        void startUp();
    private:
        int position = 0;
        unsigned long loopCount = 0;
        float frequency; // frequency at which you're calling evaluate.  (Hertz)
        int buffer[BUFFER_SIZE];
        int pinA, pinB; // check to make sure these pins are plugged into the A and B channels on the mag encoder
        unsigned long time; // micros()

        int currentA = 0, lastA = 0; // the current and latest reading on signal A
};

encoder::encoder(int digital_pin_A, int digital_pin_B) {
    pinA = digital_pin_A;
    pinB = digital_pin_B;
}

void encoder::startUp() {
    pinMode(pinA,INPUT);
    pinMode(pinB,INPUT);
}

void encoder::evaluate() {    
    currentA = digitalRead(pinA);
    if (lastA != currentA && lastA == 0) // signifies a change in the pace
    {
        // anything inside this if statement does not necessarily happen every loop of main. 
        // If we put computationally demanding code in here main will not run at a constant pace which messes with speed readings
        if (digitalRead(pinB)) // if pinB is high, we can assume we're going forward (counterclockwise)
        { 
            position++;
        } else {
            position--;
        }
        // Serial.println(count);
    }
    lastA = currentA;
    loopCount++; // loopCount is going to get very big. since we're incrementing every evaluation
    if (loopCount % 1000 == 0) { // conversion to Milliseconds, assuming we're evaluating at a frequency of 1 megahertz
        buffer[(loopCount/1000) % BUFFER_SIZE] = position;
    }
    // by storing position in this way, the position we stored a time longest ago is always stored in the 
    //        (loopCount+1)%BUFFER_SIZE 
    // space. 

} // this should happen every chance you get

int encoder::getPosition() {
    return position;
} 

float encoder::getSpeed() {
    // v = dx/dt = (x_2 - x_1)/ (BUFFER_SIZE/frequency)
    // unfortunately, frequency is not constant throughout the execution, so this may lead us to some problems.
    // I can imagine keeping a list of timestamps for every evalution of position that we reference to get our speed over the interval
    return (buffer[loopCount%BUFFER_SIZE] - buffer[(loopCount+1)%BUFFER_SIZE])*frequency / BUFFER_SIZE;
}

void encoder::zeroPosition() {
    position = 0;
} // useful for redoing a movement
