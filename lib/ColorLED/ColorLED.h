#ifndef ___Class_ColorLED
#define ___Class_ColorLED
#include "Arduino.h"
#include "DigitalPin.h"
class ColorLED {
private:
    DigitalPin red, green, blue;

public:
    ColorLED(int redPin, int greenPin, int bluePin);
    void writeRed(bool mode);
    void writeGreen(bool mode);
    void writeBlue(bool mode);
};

#endif
