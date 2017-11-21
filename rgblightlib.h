/*rgblightlib
* A library for non interupting lighting effects
* Pim Ostendorf - 2017
*/

#ifndef rgblightlib_h
#define rgblightlib_h
#include "Arduino.h"

class llib
{
    public:
    //public variables and fucntions
        llib(int pin);
        void breathSingle(int speed);
        void blinkSingle(int speed);
        void blinkSingle(int timeHigh, int timeLow);
        void flickerSingle();
        void flickerSingle(int intMin, int intMax);
        void flickerSingle(int intMin, int intMax, int speed);
        //void patternSingle(int[] pattern, int speed);
        void update();
    private:
    //private variables and fucntion
        //gobal variables
        int _pin;

        //variables for blinking
        unsigned long milBlink;
        bool ioBlink = false;

        //variables for breathing
        unsigned long milBreath;

        //variables for flickering
        unsigned long milFlicker;

        //variables for pattern function
        unsigned long milPattern;
};

#endif