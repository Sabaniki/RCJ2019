#ifndef ___Cpp_Move
#define ___Cpp_Move
#include "ServoPin.h"
#include "Motor.h"
#include "Arduino.h"
#include "Servo.h"


ServoPin::ServoPin(int pin, Servo myServo):pin(pin),myServo(myServo){
    myServo.attach(pin);
}

inline void ServoPin::write(int angle){
    myServo.write(angle);
}

inline void ServoPin::getPinNumber(){
    return pin;
}

inline void ServoPin::getServo(){
    return myServo;
}
#endif