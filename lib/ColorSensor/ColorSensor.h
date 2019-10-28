#ifndef ___Class_ColorSensor
#define ___Class_ColorSensor
#include "ColorLED.h"
#include "AnalogPin.h"
class ColorSensor {
private:
    int thresholds[3][3];
    ColorLED light;
    AnalogPin reader;
    int aveR, aveG, aveB;
	const int colorNum = 3;
	const int loopNum = 10;
	int mined[3][3];
	int colorArray[3];
	int readValue[3];
	int copyedColorArray[3];
	const char G = 'G', W = 'W', Bl = 'B';

public:
    ColorSensor(int Rpin, int Gpin, int Bpin, int readerPin, const int (&thresholdsRGB)[3][3]);

    int readValueRed();
    int readValueGreen();
    int readValueBlue();
    char read();
};

#endif
