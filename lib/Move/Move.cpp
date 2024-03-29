#ifndef ___Cpp_Move
#define ___Cpp_Move
#include "Move.h"
#include "Motor.h"
#include "Motor.cpp"
#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"
#include "Arduino.h"

Move::Move(Motor motorL, Motor motorR, RotaryEncoder rotaryEncoderL, RotaryEncoder rotaryEncoderR):
    motorL(motorL),
    motorR(motorR),
    rotaryEncoderL(rotaryEncoderL),
    rotaryEncoderR(rotaryEncoderR){

}

void Move::straight(int speed){
    motorL.write(speed);
    motorR.write(speed  * offSet);
}

// NOT USING ROTARYENCODER
void Move::straight(int speed, int distance){ 
    motorL.write(speed);
    motorR.write(speed * offSet);
    delay(distance);
    // int leftPower = 0, rightPower = 0;
    // const int L = 0, R = 1;
    // bool state[2] = {true, true};
    // while (state[L] || state[R]){
    //     if (state[L])
    //         state[L] = rotaryEncoderL.until(distance);
    //     else if (state[R])
    //         state[R] = rotaryEncoderR.until(distance);

    //     if (state[L])
    //         leftPower = speed;
    //     else{
    //         state[L] = false;
    //         leftPower = 0;
    //     }

    //     if (state[R])
    //         rightPower = speed;
    //     else{
    //         state[R] = false;
    //         rightPower = 0;
    //     }

    //     write(leftPower, rightPower);
    // }
    stop(false);
}

void Move::back(int speed){
    motorL.write(-speed);
    motorR.write(-speed  * offSet);
}

void Move::back(int speed, int length){
    // while(rotaryEncoder.until(length)){
    //     motorL.write(-speed);
    //     motorR.write(-speed);
    // }
    motorL.write(-speed);
    motorR.write(-speed  * offSet);
    delay(length);
}

void  Move::right(int speed, bool rotate){
    speed *= 1.5;
    if(rotate){
        motorL.write(speed);
        motorR.write(-speed  * offSet);
    }
    else {
        motorL.write(speed);
        motorR.write(0);
    }
}
void  Move::left(int speed, bool rotate){
    speed *= 1.5;
    if(rotate){
        motorL.write(-speed);
        motorR.write(speed  * offSet);
    }
    else {
        motorL.write(0);
        motorR.write(speed  * offSet);
    }
}

void Move::stop(bool strong){
    if(strong){
        motorL.write(-255);
        motorR.write(-255);
        delay(10);
    }
    else {
        motorL.write(0);
        motorR.write(0);
    }
}

void Move::write(int leftSpeed, int rightSpeed){
    motorL.write(leftSpeed);
    motorR.write(rightSpeed  * offSet);
}

// このメソッドあんまいらないかもしれない
#endif