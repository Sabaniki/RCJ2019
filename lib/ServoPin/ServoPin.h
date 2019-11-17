#ifndef ___Class_ServoPin
#define ___Class_ServoPin
#include "Servo.h"
#include "Variables.h"

class ServoPin{
    private:
        int pin;
        Servo myServo;

    public:
        ServoPin(int pin, Servo myservo);
        void write(int angle);
        int getPinNumber();
        Servo getServoName();
};

#endif