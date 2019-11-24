#ifndef ___Class_Move
#define ___Class_Move
#include "Motor.h"
#include "Motor.cpp"
#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"
class Move {
private:
    Motor motorL, motorR;
    RotaryEncoder rotaryEncoderL, rotaryEncoderR;
    int offSet = 1.3;

public:
    Move(Motor motorL, Motor motorR, RotaryEncoder rotaryEncoderL, RotaryEncoder rotaryEncoderR);
    void straight(int speed);
    void straight(int speed, int length);
    void back(int speed);
    void back(int speed, int length);
    void right(int speed, bool rotate);
    void left(int speed, bool rotate);
    void stop(bool strong);
    void write(int leftSpeed, int rightSpeed);
    void write(int leftSpeed, int rightSpeed, int length);
};

#endif
