#ifndef ___Class_Move
#define ___Class_Move
#include "Motor.h"
#include "Motor.cpp"
class Move {
private:
    Motor motorL, motorR;
    RotaryEncoder rotaryEncoder;

public:
    Move(Motor motorL, Motor motorR, RotaryEncoder rotaryEncoder);
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
