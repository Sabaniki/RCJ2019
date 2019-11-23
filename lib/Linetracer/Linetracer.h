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
    PhotoReflector lineSensors[5] = {
        PhotoReflector(LINE_SENSOR_PIN_1),
        PhotoReflector(LINE_SENSOR_PIN_2),
        PhotoReflector(LINE_SENSOR_PIN_3),
        PhotoReflector(LINE_SENSOR_PIN_4),
        PhotoReflector(LINE_SENSOR_PIN_5),
    };
    const int colorThresholdsL[3][3] = { 
        { 27, 65, 47 },  //G
        { 80, 127, 92 },  //W
        { 30, 58, 44 },  //B
    };

    const int colorThresholdsR[3][3] = { 
        { 27, 65, 47 },  //G
        { 80, 127, 92 },  //W
        { 30, 58, 44 },  //B
    };

    // {0: 左, 1: 右}
    ColorSensor colorSensors[2] = {
        ColorSensor(
            COLOR_SENSOR_RED_PIN,
            COLOR_SENSOR_GREEN_PIN,
            COLOR_SENSOR_BLUE_PIN,
            COLOR_SENSOR_L_READER_PIN,
            colorThresholdsL
        ),
        ColorSensor(
            COLOR_SENSOR_RED_PIN,
            COLOR_SENSOR_GREEN_PIN,
            COLOR_SENSOR_BLUE_PIN,
            COLOR_SENSOR_R_READER_PIN,
            colorThresholdsR
        ),
    };

    DigitalPin tiltSensor;

    enum PhtNums{
        LL, L, C, R, RR
	};
    enum Colors{
        WW, GW, WG, GG, MV, BNP
    };

    bool lineResult[5] = { false, false, false, false, false };
    
    void kingOfJudge();
    void newKingOfJudge();
    Colors BNB_Judge();
    Colors judgeColor(int time);
    const char* colorsToString(Linetracer::Colors color);
    void finalJudge(unsigned int untilTime);
    void T_Junction();
    void crossJunction();
    void avoid();


    int speed = SPEED;
    const int slowSpeed = SLOW_SPEED;
    const int straightLength = STRAIGHT_LENGH;
    const int backLength = BACK_LENGH;
    int REN = 0;
    const int RENlength = REN_LENGTH;
    int blackSum = 0;
    Linetracer::Colors colorResult = MV;
    DigitalPin switches[2] = {
        DigitalPin(SWITCH_PIN_L, INPUT_PULLUP),
        DigitalPin(SWITCH_PIN_R, INPUT_PULLUP),
    };

public:
    Linetracer();
    bool run();
    void right90();
    void left90();
};

#endif
