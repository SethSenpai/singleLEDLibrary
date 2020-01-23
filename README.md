# Non Interupting Single LED Library
This is an arduino library meant to make it easier to implement simple lighting effects that do not interrupt the rest of the program with the dreaded `delay()` function.
The functions in the library can be called in 2 ways. One way treats the function like a *state change*. This essentially means that you use a command once to change the behaviour of that LED. Everything else is then handled by the `obj.update()` command. The other way is to call the functions yourself as part of your *program loop*. This means that the `obj.update()` function is not needed but does allow for more control over what the LED will be doing. These two methods can be used together. **Do not worry there are examples further down!**

### Before you start
Keep in mind that the blink functions will work on digital ports but everything else needs a PWM enabled port. (Look for the `~` symbol on your Arduino.)

`objectName.update()` always needs to be called in the `void loop()` when you're using the *state change* method.

### State change example
```cpp
//include the library in the program
#include <singleLEDLibrary.h>

//declare your led objects that you will be using, light1 is connected to pin 9 and light 2 to pin 10
sllib light1(9);
sllib light2(10);

void setup() {
  //we make sure that our led's are doing something on startup
  light1.setBlinkSingle(500);
  light2.setBreathSingle(500);

  //we have a button hooked up to pin 13
  pinMode(13,INPUT_PULLUP);
}

void loop() {

  //we call the update function for both led's here. Don't forget these!
  light1.update();
  light2.update();

  //if the button is pushed down we set light2 to be off.
  //when the button is not pressed it breathes.
  if(digitalRead(13) == LOW){
    light2.setOffSingle();
  }
  else
  {
    light2.setBreathSingle(500);
  }

}
```
As you can see in the above example we're using the `set` functions so toggle the state of the LED. `light1.update();` makes sure that the LED's actually light up.

## In loop example
```cpp
//include the library in your program
#include <singleLEDLibrary.h>

//declare your led objects that you will be using, light1 is connected to pin 9 and light 2 to pin 10
sllib light1(9);
sllib light2(10);

void setup() {
  //we have a button hooked up to pin 13
  pinMode(13,INPUT_PULLUP);
}

void loop() {
  //we make sure that light1 is blinking
  light1.blinkSingle(500);
  
  //if the button is pushed down light2's breathing is interrupted.
  //when the button is not pressed it breathes.
  if(digitalRead(13) == HIGH){
    light2.breathSingle(500);
  }
}
```
This example shows the way the functions can be implemented *in loop*. We don't define the states of the LED's we just call the functions every time that tell the LED what to do in the next loop of the program.

## Function Reference

#### Instantiate object
```cpp
sllib nameoftheLED(int pinNumber);
```
Set up the light object that you will be using for the rest of the program. The `nameoftheLED` can be called anything.

#### Update
*state change **only***
```cpp
update();
```
Needed to update the LEDS when using the state change method. *This function needs to be put in the `void loop()`.

#### Turn LED on
*state change*
```cpp
setOnSingle();
```
Turns the LED on.

#### Turn LED off
*state change*
```cpp
setOffSingle();
```
Turns off the LED.

#### Breathing
*in loop*
```cpp
breathSingle(int speed);
```
*state change*
```cpp
setBreathSingle(int speed);
```
A breathing animation for an LED. The `speed` is the time elapsed for 1 breath to be taken in milliseconds.

#### Blinking
*in loop*
```cpp
blinkSingle(int speed);
blinkSingle(int speedHigh, speedLow);
blinkRandomSingle(int minTime, int maxTime);
```
*state change*
```cpp
setBlinkSingle(int speed);
```
A blinking animation for an LED. This function encompasses several different animations. `speed` is the time in milliseconds that the LED will turn off or on for. `speedHigh` and `speedLow` allow you to set the time of the on and off state independently. 
`blinkRandomSingle` is a bit of an odd one out here but this allows you to set an LED to blink randomly between a minimum value and a maximum value.

#### Flickering
*in loop*
```cpp
flickerSingle();
flickerSingle(int min, int max);
flickerSingle(int min, int max, int speed);
```
*state change*
```cpp
setFlickerSingle();
```
Flickers the LED, tries to simulate a flame. `min` and `max` define the higher and lower bounds of the LED's intensity. `speed` allows you to fine-tune the refresh speed of the animation. Play around with the values to see what works for you best.

#### Pattern Blinking
*in loop*
```cpp
patternSingle(int pattern[], int arraylength);
```
*state change*
```cpp
setPatternSingle(int pattern[], int arraylength);
```
This function allows you to define a pattern for blinking beforehand and display this pattern on your LED. The function takes an array that represents the pattern.
```cpp
int pattern[] = {100,500,100,1000};
```
This array will make the LED turn on for *100* ms and then off for *500*, on again for *100* then off again for *1000*, before it turns on again and starts the loop from the start. **Keep in mind that the first value turns the led on but if you have an uneven array it will shift every other loop.**

`arraylength` is the length of the array that you defined.