# Non Interupting Single LED Library
This is an arduino library meant to make it easier to implement simple lighting effects that do not interrupt the rest of the program with the dreaded `delay()` function.
The functions in the library can be called in 2 ways. One way treats the function like a *state change*. This essentially means that you use a command once to change the behaviour of that LED. Everything else is then handled by the `obj.update()` command. The other way is to call the functions yourself as part of your *program loop*. This means that the `obj.update()` function is not needed but does allow for more control over what the LED will be doing. **Do not worry there are examples further down!**

### State change example
```cpp
#include <singleLEDLibrary.h>

sllib light1(9);
sllib light2(10);
sllib light3(11);
int p1[] = {300,300,2000,300};
int p2[] = {500,50,2000,50};

int r = 1;
bool pushdown = false;

void setup() {
  // put your setup code here, to run once:
  light1.setBlinkSingle(500);
  light2.setBreathSingle(500);
  light3.setPatternSingle(p1,4);

  pinMode(13,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  light1.update();
  light2.update();
  light3.update();

  if(digitalRead(13) == LOW && pushdown == false){
    r++;
    pushdown = true;
  }
  if(digitalRead(13) == HIGH && pushdown == true){
    pushdown = false;
  }

  if(r % 2 == 0){
     light3.setPatternSingle(p2,4);
  }
  else
  {
     light3.setPatternSingle(p1,4);
  }
}
```