#ifndef ___Class_Linetracer
#define ___Class_Linetracer
#pragma region includes
#include "Arduino.h"
#include "PhotoReflector.h"
#include "Move.h"
#pragma endregion
class Linetracer {
private:
    Move manager;
    PhotoReflector phts[5] = {
        PhotoReflector(0),
        PhotoReflector(1),
        PhotoReflector(3),
        PhotoReflector(4),
        PhotoReflector(5),
    };
public:
    Linetracer();
    void run();
};

#endif
