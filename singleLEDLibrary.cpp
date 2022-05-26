#include "singleLEDLibrary.h"
#include "Arduino.h"

#define P_NONE       0
#define P_SINGLE     1
#define P_BREATHE    2
#define P_FLICKER    3
#define P_BLINK      4
#define P_BLINK_RAND 5

sllib::sllib(int pin){
    //make sure to use pwm ports here
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);
    _pin = pin;
}

void sllib::update(){
    switch(runningFunction){
        case P_NONE:
        break;
        case P_SINGLE:
            patternSingle(arrP,speedp);
        break;
        case P_BREATHE:
            breathSingle(speedp);
        break;
        case P_FLICKER:
            flickerSingle();
        break;
        case P_BLINK:
            blinkSingle(speedp);
        break;
        case P_BLINK_RAND:
            blinkRandomSingle(speedp,timep);
        break;
    }
}

void sllib::setOnSingle(){
    runningFunction = P_NONE;
    digitalWrite(_pin, HIGH);
}

void sllib::setOffSingle(){
    runningFunction = P_NONE;
    digitalWrite(_pin, LOW);
}

void sllib::setRandomBlinkSingle(int minTime, int maxTime){
    runningFunction = P_BLINK_RAND;
    speedp = minTime;
    timep = maxTime;
}

void sllib::setPatternSingle(int pattern[], int lengthArray){
    if (arrP != 0) {
    delete [] arrP;
    }
    arrP = new int [lengthArray];

    for(int i=0; i < lengthArray; i++){
        arrP[i] = pattern[i];
    }
    speedp = lengthArray;
    runningFunction = P_SINGLE;
}

void sllib::setBreathSingle(int speed){
    runningFunction = P_BREATHE;
    speedp = speed;
}

void sllib::setFlickerSingle(){
    runningFunction = P_FLICKER;
}

void sllib::setBlinkSingle(int speed){
    runningFunction = P_BLINK;
    speedp = speed;
}

//function for pattern based blinking, first entry always turns the led high
void sllib::patternSingle(int pattern[], int lengthArray){
    if(counter < lengthArray) {
        if(milOld == 0){
            milOld = millis();
            digitalWrite(_pin,HIGH);
        }
        if((milOld + pattern[counter]) < millis() ){
            milOld = millis();
            if(counter % 2 == 0){
                digitalWrite(_pin, LOW);
            }
            else{
                digitalWrite(_pin,HIGH);
            }
            counter++;
        }
    }
    else{
        counter = 0;
    }
}

// simple breating function
void sllib::breathSingle(int speed){
    if((milOld + 1) < millis() ){
        milOld = millis();
        float it = 0;
        it = (exp(sin(millis()/(float)speed*PI)) - 0.36787944)*108.0;
        analogWrite(_pin, it);
    }
}

// simple flickering function
void sllib::flickerSingle(int intMin, int intMax){
    if((milOld + 100) < millis()){
        milOld = millis();
        float it = 0;
        it = random(intMin,intMax);
        analogWrite(_pin, it);
    }
}

//overload for instant use
void sllib::flickerSingle(){
    if((milOld + 100) < millis()){
        milOld = millis();
        float it = 0;
        it = random(80,255);
        analogWrite(_pin, it);
    }
}

//overload for speed controll
void sllib::flickerSingle(int intMin, int intMax, int speed){
    if((milOld + speed) < millis()){
        milOld = millis();
        float it = 0;
        it = random(intMin,intMax);
        analogWrite(_pin, it);
    }
}

// simple blinking function
void sllib::blinkSingle(int speed){
    if ( (milOld + speed) < millis() ) {
        milOld = millis();
        if(ioBlink == false){
            digitalWrite(_pin,HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin,LOW);
            ioBlink = false;
        }
    }
}

//overload to allow for async blinking
void sllib::blinkSingle(int timeHigh, int timeLow){
    if(ioBlink == false){
        if( (milOld + timeHigh) < millis()){
            milOld = millis();
            digitalWrite(_pin,LOW);
            ioBlink = true;
        }
    }
    else{
        if((milOld + timeLow) < millis()){
            milOld = millis();
            digitalWrite(_pin,HIGH);
            ioBlink = false;
        }
    }
}

//blinking with randomised delay
void sllib::blinkRandomSingle(int minTime, int maxTime){
    if((milOld + rndTemp) < millis()){
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if(ioBlink == false){
            digitalWrite(_pin,HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin,LOW);
            ioBlink = false;
        }
    }
}