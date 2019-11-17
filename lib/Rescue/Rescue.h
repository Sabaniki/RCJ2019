#ifndef ___Class_Rescue
#define ___Class_Rescue

#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "UltrasonicSensor.h"
#include "UltrasonicSensor.cpp"
#include "ServoPin.h"
#include "ServoPin.cpp"
#include "Servo.h"
#include "RescueVariables.h"
#include "Variables.h"

class Rescue{
    private:
        Move manager;
        Servo front;
        Servo back;
        ServoPin servos[2]{
            ServoPin(SRV_PIN_1,front),
            ServoPin(SRV_PIN_2,back)
        };

        UltrasonicSensor ultrasonicSensors[2]{
            UltrasonicSensor(ULT_TRIG_PIN_1,ULT_ECHO_PIN_1),
            UltrasonicSensor(ULT_TRIG_PIN_2,ULT_ECHO_PIN_2)
        };

        RotaryEncoder rotaryEncoders[2]{
            RotaryEncoder(ROTARY_ENCODER_READER_PIN_1,THRESHOLD_RRTE),
            RotaryEncoder(ROTARY_ENCODER_READER_PIN_2,THRESHOLD_RRTE)
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
        void up(int mode);
        void down(int mode);
        bool run();
};

#endif