#ifndef ___Class_Resucue
#define ___Class_Resucue
#include "ServoPin.h"
#include "ServoPin.cpp"
#include "Servo.h"
#include "Variables.h"

class ServoPin{
    private:
        int pin;
        Servo myServo;

    public:
        Rescue();
        bool Judge();
        


};

#endif