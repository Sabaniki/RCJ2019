#ifndef ___Class_Linetracer
#define ___Class_Linetracer
#pragma region includes
#include "Arduino.h"
#include "PhotoReflector.h"
#include "Move.h"
#include "ColorSensor.h"
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
    enum PhtNums{
        LL, L, C, FC, R, RR
	};

    bool readLineResult[5] = { false, false, false, false, false };
    void adjustment();
    char judgeColor();

public:
    Linetracer();
    void run();
};

#endif
