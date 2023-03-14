#include "Arduino.h"
#include <Wire.h>

class Keypad3x3{

  public:
    Keypad3x3(byte X,byte Y,byte Z,byte A,byte B,byte C);
    void Init(void);
    int getKey(void);
    char getKeyChar(void);
  private:
    byte _KEY_X;
    byte _KEY_Y;
    byte _KEY_Z;
    byte _KEY_A;
    byte _KEY_B;
    byte _KEY_C;
    int previousButtonState = HIGH;
    int ButtonState = LOW;
};