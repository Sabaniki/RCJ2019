#ifndef ___Class_Linetracer
#define ___Class_Linetracer

#pragma region includes
#include "Arduino.h"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#pragma endregion

class Linetracer {
private:
    Move manager;
    PhotoReflector phts[5] = {
        PhotoReflector(0),
        PhotoReflector(1),
        PhotoReflector(2),
        PhotoReflector(3),
        PhotoReflector(4),
    };
    int colorThresholds[2] = {1, 1};
    ColorSensor colorSensors[2] = {
        ColorSensor(5, 6, 7, colorThresholds),
        ColorSensor(8, 9, 10, colorThresholds)
    };

    enum PhtNums{
        LL, L, C, FC, R, RR
	};
    enum Colors{
        WW, GW, WG, GG
    };

    bool lineResult[5] = { false, false, false, false, false };
    char colorResult[5];
    void adjustment();
    Colors judgeColor();

    int speed = 255;
    int slowSpeed = 220;
    int straightLength = 30;
    int backLength = 10;
    int REN = 0;
    int RENlength = 10;

public:
    Linetracer();
    void run();
    void right90();
    void left90();
};

#endif
