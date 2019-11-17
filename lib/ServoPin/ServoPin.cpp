#ifndef ___Cpp_ServoPin
#define ___Cpp_ServoPin
#include "ServoPin.h"
#include "ServoPin.cpp"
#include "Arduino.h"


ServoPin::ServoPin(int pin, Servo myServo):pin(pin),myServo(myServo){
    myServo.attach(pin);
}
/*
~ServoPin(){
    myServo.detach();//たぶんあってる気がする。
}
*/
void ServoPin::write(int angle){
    myServo.write(angle);
}

int ServoPin::getPinNumber(){
    return pin;
}

Servo ServoPin::getServoName(){
    return myServo;
}
#endif