#ifndef ___Class_Resucue
#define ___Class_Resucue
#include "Rescue.h"
#include "Rescue.cpp"
#include "Motor.h"
#include "Motor.cpp"
#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "Variables.h"

class Rescue{
    private:
        Move manager
        PhotoReflector phts[5] = {
        PhotoReflector(PHT_PIN_1),
        PhotoReflector(PHT_PIN_2),
        PhotoReflector(PHT_PIN_3),
        PhotoReflector(PHT_PIN_4),
        PhotoReflector(PHT_PIN_5),
    };
        Motor motorL, motorR
        RotaryEncoder rotaryEncoder
    public:

};

#endif