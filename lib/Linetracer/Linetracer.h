#ifndef ___Class_Linetracer
#define ___Class_Linetracer

#include "Variables.h"
#include "Arduino.h"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#include "KuromikaLine.h"
#include "KuromikaLine.cpp"

class Linetracer {
private:
    Move manager;
    KuromikaLine lineSensors[5] = {
        KuromikaLine(LINE_GREEN_PIN, LINE_SENSOR_PIN_1, LINE_SENSOR_THRESHOLD),
        KuromikaLine(LINE_GREEN_PIN, LINE_SENSOR_PIN_2, LINE_SENSOR_THRESHOLD),
        KuromikaLine(LINE_GREEN_PIN, LINE_SENSOR_PIN_3, LINE_SENSOR_THRESHOLD),
        KuromikaLine(LINE_GREEN_PIN, LINE_SENSOR_PIN_4, LINE_SENSOR_THRESHOLD),
        KuromikaLine(LINE_GREEN_PIN, LINE_SENSOR_PIN_5, LINE_SENSOR_THRESHOLD),
    };
    int colorThresholds[2] = { THRESHOLD_RED, THRESHOLD_GREEN };
    // {0: 左, 1: 右}
    ColorSensor colorSensors[2] = {
        ColorSensor(
            COLOR_SENSOR_L_RED_PIN,
            COLOR_SENSOR_L_GREEN_PIN,
            COLOR_SENSOR_L_READER_PIN,
            colorThresholds
        ),
        ColorSensor(
            COLOR_SENSOR_R_RED_PIN,
            COLOR_SENSOR_R_GREEN_PIN,
            COLOR_SENSOR_R_READER_PIN,
            colorThresholds
        ),
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

    const int speed = SPEED;
    const int slowSpeed = SLOW_SPEED;
    const int straightLength = STRAIGHT_LENGH;
    const int backLength = BACK_LENGH;
    int REN = 0;
    const int RENlength = REN_LENGTH;

public:
    Linetracer();
    bool run();
    void right90();
    void left90();
};

#endif
