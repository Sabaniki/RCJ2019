#ifndef ___Cpp_Resucue
#define ___Cpp_Resucue
#include "Arduino.h"
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

Rescue::Rescue() : manager(
                       Motor(MOTOR_L_FRONT_PIN, MOTOR_L_BACK_PIN),
                       Motor(MOTOR_R_FRONT_PIN, MOTOR_R_BACK_PIN),
                       RotaryEncoder(ROTARY_ENCODER_READER_PIN, THRESHOLD_RRTE))
{
    front.attach(SRV_PIN_1);
    back.attach(SRV_PIN_2);
}

bool Rescue::judge()
{
    bool result = false;
    int distances[2] = {0, 0};
    for (size_t i = 0; i < 2; i++)
        distances[i] = ultrasonicSensors[i].readDistance();
    if (distances[0] < length && distances[1] < length)
        result = true;
    return result;
}

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
            rightPower = speed;
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
        front.write(FRONT_UP_ANGLE);
        break;
    case 2: //back(tail)をあげる
        back.write(BACK_UP_ANGLE);
        break;
    case 3:
        for (int i = FRONT_DOWN_ANGLE; i < FRONT_UP_ANGLE; i += 5)
        {
            front.write(i);
            delay(10);
        }
        break;

    case 4:
        for (int i = BACK_DOWN_ANGLE; i < BACK_UP_ANGLE; i += 5)
        {
            back.write(i);
            delay(10);
        }
        break;

    default:
        //Serial.println("default");
        break;
    }
    delay(500);
}

void Rescue::down(int mode)
{
    switch (mode)
    {
    case 1: //front(arm)をさげる
        front.write(FRONT_DOWN_ANGLE);
        break;
    case 2: //back(tail)をさげる
        back.write(BACK_DOWN_ANGLE);
        break;

    case 3:
        for (int i = FRONT_UP_ANGLE; i > FRONT_DOWN_ANGLE; i -= 5)
        {
            front.write(i);
            delay(10);
        }
        break;

    case 4:
        for (int i = BACK_UP_ANGLE; i > BACK_DOWN_ANGLE; i -= 5)
        {
            back.write(i);
            delay(10);
        }
        break;

    default:
        break;
    }
    delay(500);
}

bool Rescue::run()
{
    return true;
}
#endif