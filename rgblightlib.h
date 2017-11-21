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
        
        //breathing
        void breathSingle(int speed);

        //blink
        void blinkSingle(int speed);
        void blinkSingle(int timeHigh, int timeLow);
        
        //flicker
        void flickerSingle();
        void flickerSingle(int intMin, int intMax);
        void flickerSingle(int intMin, int intMax, int speed);
        
        //blink pattern
        void patternSingle(int pattern[], int speed);
        
        //future update function
        void update();
    private:
    //private variables and fucntion
        //gobal variables
        int _pin;
        unsigned long milOld;

        //variables for blinking
        bool ioBlink = false;

        //variables for pattern
        int counter = 0;
        int odd = true;
};

#endif