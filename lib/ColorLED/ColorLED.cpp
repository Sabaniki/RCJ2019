#include "ColorLED.h"
#include "Arduino.h"

ColorLED::ColorLED(int redPin, int greenPin, int bluePin): 
    red(redPin, OUTPUT), green(greenPin, OUTPUT), blue(bluePin, OUTPUT)  {

}

inline void ColorLED::writeRed(bool mode){
    red.write(mode);
}

inline void ColorLED::writeGreen(bool mode){
    green.write(mode);
}

inline void ColorLED::writeBlue(bool mode){
    blue.write(mode);
}