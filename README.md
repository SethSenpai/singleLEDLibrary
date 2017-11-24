# Non Interupting Single LED Library
This is an arduino library meant to make it easier to implement simple lighting effects that do not interrupt the rest of the program with the dreaded `delay()` function.
The functions in the library can be called in 2 ways. One way treats the function like a *state change*. This essentially means that you use a command once to change the behaviour of that LED. Everything else is then handled by the `obj.update()` command. The other way is to call the functions yourself as part of your *program loop*. This means that the `obj.update()` function is not needed but does allow for more control over what the LED will be doing. These two methods can be used together. **Do not worry there are examples further down!**

### State change example
```cpp
//include the library in the program
#include <singleLEDLibrary.h>

//declare your led objects that you will be using, light1 is connected to pin 9 and light 2 to pin 10
sllib light1(9);
sllib light2(10);

bool onOrOff = false;
bool pushdown = false;

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

bool onOrOff = false;
bool pushdown = false;

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
Set up the light object that you will be using for the rest of the program.