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
#include "ServoPin.h"
#include "ServoPin.cpp"
#include "Variables.h"

class Rescue{
    private:
        Move manager;

        ServoPin servos[2]{
            ServoPin(SRV_PIN_1,SRV_NAME_1),
            ServoPin(SRV_NAME_2,SRV_PIN_2)
        };

        UltrasonicSensor ultrasonicSensors[2]{
            UltrasonicSensor(ULT_TRIG_PIN_1,ULT_ECHO_PIN_1),
            UltrasonicSensor(ULT_TRIG_PIN_2,ULT_ECHO_PIN_2)
        };

        RotaryEncoder rotaryEncoders[2]{
            RotaryEncoder(ROTARY_ENCODER_READER_PIN_1),
            RotaryEncoder(ROTARY_ENCODER_READER_PIN_2)
        };

        const int length = BLOCK_LENGTH;
        const int speed = SPEED;
        const int slowSpeed = SLOW_SPEED;
    public:
        Rescue();
        bool judge();
        void goStraight(int distance);
        void left90();
        void right90();
        void up();
        void down();
};

#endif