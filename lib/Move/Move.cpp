#ifndef ___Cpp_Move
#define ___Cpp_Move
#include "Move.h"
#include "Motor.h"
#include "Motor.cpp"
#include "Arduino.h"

Move::Move(Motor motorL, Motor motorR): motorL(motorL), motorR(motorR) {

}

void Move::straight(int speed){
    motorL.write(speed);
    motorR.write(speed);
}

// NOT_INMPLEMENTED
void Move::straight(int speed, int length){ 
    while(true/* 終了条件とかそんな感じのこと */){
        motorL.write(speed);
        motorR.write(speed);
    }
}

void Move::back(int speed){
    motorL.write(-speed);
    motorR.write(-speed);
}

void Move::back(int speed, int length){
    while(true/* 終了条件とかそんな感じのこと */){
        motorL.write(-speed);
        motorR.write(-speed);
    }
}

void  Move::right(int speed, bool rotate){
    if(rotate){
        motorL.write(speed);
        motorR.write(-speed);
    }
    else {
        motorL.write(speed);
        motorR.write(0);
    }
}
void  Move::left(int speed, bool rotate){
    if(rotate){
        motorL.write(-speed);
        motorR.write(speed);
    }
    else {
        motorL.write(0);
        motorR.write(speed);
    }
}

void Move::stop(bool strong){
    if(strong){
        motorL.write(-255);
        motorR.write(-255);
        delay(50);
    }
    else {
        motorL.write(-255);
        motorR.write(-255);
    }
}

void Move::write(int leftSpeed, int rightSpeed){
    motorL.write(leftSpeed);
    motorR.write(rightSpeed);
}
#endif