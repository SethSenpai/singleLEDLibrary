#include "rgblightlib.h"
#include "Arduino.h"



llib::llib(int pin){
    //make sure to use pwm ports here
    pinMode(pin,OUTPUT);
    _pin = pin;
}

void llib::update(){

}

//function for pattern based blinking
void llib::patternSingle(String pattern, int speed){
    if((milPattern + speed) < millis() ){
        milPattern = millis();

    }
}

// simple breating function
void llib::breathSingle(int speed){
    if((milBreath + 1) < millis() ){
        milBreath = millis();
        float it = 0;
        it = (exp(sin(millis()/(float)speed*PI)) - 0.36787944)*108.0;
        analogWrite(_pin, it);
    }
}

// simple flickering function
void llib::flickerSingle(int intMin, int intMax){
    if((milFlicker + 100) < millis()){
        milFlicker = millis();
        float it = 0;
        it = random(intMin,intMax);
        analogWrite(_pin, it);
    }
}

//overload for instant use
void llib::flickerSingle(){
    if((milFlicker + 100) < millis()){
        milFlicker = millis();
        float it = 0;
        it = random(80,255);
        analogWrite(_pin, it);
    }
}

//overload for speed controll
void llib::flickerSingle(int intMin, int intMax, int speed){
    if((milFlicker + speed) < millis()){
        milFlicker = millis();
        float it = 0;
        it = random(intMin,intMax);
        analogWrite(_pin, it);
    }
}

// simple blinking function
void llib::blinkSingle(int speed){
    if ( (milBlink + speed) < millis() ) {
        milBlink = millis();
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