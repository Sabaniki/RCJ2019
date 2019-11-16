#ifndef ___Cpp_Resucue
#define ___Cpp_Resucue
#include "Rescue.h"
#include "Rescue.cpp"
#include "Motor.h"
#include "Motor.cpp"
#include "Move.h"
#include "Move.cpp"
#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"
#include "UltrasonicSensor.h"
#include "UltrasonicSensor.cpp"
#include "Arduino.h"
Rescue::Rescue()
{
    manager(
        Motor(MOTOR_L_FRONT_PIN, MOTOR_L_BACK_PIN),
        Motor(MOTOR_R_FRONT_PIN, MOTOR_R_BACK_PIN),
        RotaryEncoder(ROTARY_ENCODER_READER_PIN))
}

bool Rescue::judge()
{
    bool result = false;
    int distances[2] = { 0,
                         0 } for (size_t i = 0; i < 2; i++)
        distances[i] = ultrasonicSensors[i].readDistance();
    if (ultrasonicSensors[0] < length && ultrasonicSensor[1] < length)
        result = true;
    return result;
}

// void Rescue::goStraight(int distance){
//     int diff = 0;
//     int leftpower,rightpower;
//     bool state[2] = {false,false};
//     while((state[0] = rotaryEncoders[0].until(distance)) || (state[1] = rotaryEncoders[1].until(distance))){
//         diff = rotaryEncoders[0].getCurrentCount() - rotaryEncoders[1].getCurrentCount();//まっすぐ走るための調整動作
//         if(diff < -10){
//             leftpower = speed;
//             rightpower = 0;
//         }
//         else if(diff > 10){
//             leftpower = 0;
//             rightpower = speed;
//         }
//         else{
//             leftpower = speed;
//             rightpower = speed;
//         }
//         if(!state[0])leftpower = 0;
//         if(!state[1])rightpower = 0;
//         manager.write(leftpower,rightpower);

//     }
//     manager.stop(true);
//     delay(5);
// }

void Rescue::goStraight(int distance)
{ //脳内デバッグ一切してないから間違ってるかもしれんけどこんな感じのことが提案したかった
    int leftPower = 0, rightPower = 0;
    const int L = 0, R = 1;
    bool state[2] = {true, true};
    while (state[L] || state[R])
    {
        for (int i = 0; i < 2; i++)
            if (state[i])
                state[i] = rotaryEncoders[i].until(distance);
        if (state[L])
            leftPower = speed;
        else
        {
            state[L] = false;
            leftPower = 0;
        }
        if (state[R])
            rightPower = speed 
        else
        {
            state[R] = false;
            rightPower = 0;
        }
        manager.write(leftPower, rightPower);
    }
    manager.stop(false);
}

void Rescue::left90()
{
    manager.stop(true);
    int leftpower = -slowSpeed;
    int rightpower = slowSpeed;
    bool state[2] = {true, true};

    while (state[0] || state[1])
    {
        for (int i = 0; i < 2; i++)
            if (state[i])
                state[i] = rotaryEncoders[i].until(LEFT90);
        if (!state[0])
            leftpower = 0; //←おれの手元ではResucue.hにstate[2]: {bool, bool} が定義されてないけどこれは…？
        if (!state[1])
            rightpower = 0; //←おれの手元ではResucue.hにstate[2]: {bool, bool} が定義されてないけどこれは…？
        manager.write(leftpower, rightpower);
    }
}

void Rescue::right90()
{
    manager.stop(true);
    int leftpower = slowSpeed;
    int rightpower = -slowSpeed;
    bool state[2] = {true, true};

    while (state[0] || state[1])
    {
        for (int i = 0; i < 2; i++)
            if (state[i])
                state[i] = rotaryEncoders[i].until(RIGHT90);
        if (!state[0])
            leftpower = 0; //←おれの手元ではResucue.hにstate[2]: {bool, bool} が定義されてないけどこれは…？
        if (!state[1])
            rightpower = 0; //←おれの手元ではResucue.hにstate[2]: {bool, bool} が定義されてないけどこれは…？
        manager.write(leftpower, rightpower);
    }
}

void Rescue::up(int mode)
{
    switch (mode)
    {
    case 1: //front(arm)をあげる
        rotaryEncoders[0].write(FRONT_UP_ANGLE);
        break;
    case 2: //back(tail)をあげる
        rotaryEncoders[1].write(BACK_UP_ANGLE);
        break;
    default:
        break;
    }
    delay(500);
}

void Rescue::down(int mode)
{
    switch (mode)
    {
    case 1: //front(arm)をさげる
        rotaryEncoders[0].write(FRONT_DOWN_ANGLE);
        break;
    case 2: //back(tail)をさげる
        rotaryEncoders[1].write(BACK_DOWN_ANGLE);
        break;
    default:
        break;
    }
    delay(500);
}
#endif