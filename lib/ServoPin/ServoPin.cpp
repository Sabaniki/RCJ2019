#ifndef ___Cpp_ServoPin
#define ___Cpp_ServoPin
#include "ServoPin.h"
#include "Motor.h"
#include "Arduino.h"
#include "Servo.h"


ServoPin::ServoPin(int pin, Servo myServo):pin(pin),myServo(myServo){
    myServo.attach(pin);
}
~ServoPin(){
    myServo.detach();//たぶんあってる気がする。
}

inline void ServoPin::write(int angle){
    myServo.write(angle);
}

inline int ServoPin::getPinNumber(){
    return pin;
}

inline Servo ServoPin::getServo(){
    return myServo;
}
#endif