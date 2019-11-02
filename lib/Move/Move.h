#ifndef ___Class_Move
#define ___Class_Move
#include "Motor.h"
#include "Motor.cpp"
class Move {
private:
    Motor motorL, motorR;

public:
    Move(Motor motorL, Motor motorR);
    void straight(int speed);
    void straight(int speed, int length);
    void back(int speed);
    void back(int speed, int length);
    void right(int speed, bool rotate);
    void left(int speed, bool rotate);
    void stop(bool strong);
};

#endif
