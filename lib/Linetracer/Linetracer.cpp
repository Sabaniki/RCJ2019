#include "Linetracer.h"
#include "Arduino.h"
#include "Motor.h"
#include "Motor.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#include "RotaryEncoder.h"
#include "RotaryEncoder.cpp"

Linetracer::Linetracer():
    manager(
        Motor(MOTOR_L_FRONT_PIN, MOTOR_L_BACK_PIN),
        Motor(MOTOR_R_FRONT_PIN, MOTOR_R_BACK_PIN),
        RotaryEncoder(ROTARY_ENCODER_READER_PIN, THRESHOLD_ROTARY_ENCODER),
        RotaryEncoder(ROTARY_ENCODER_READER_PIN, THRESHOLD_ROTARY_ENCODER)
    ),
    tiltSensor(TILT_SENSOR_READER_PIN, INPUT_PULLUP){
}

void Linetracer::newKingOfJudge(){
    bool whileBlackLine[5] = { false, false, false, false, false };
    bool readLR[2] = { false, false };
    int leftPower, rightPower;
    while (true){
        for (size_t i = 0; i < 5; i++) whileBlackLine[i] = lineSensors[i].read();
        if(whileBlackLine[L]) readLR[0] = true;
        else if(whileBlackLine[R]) readLR[1] = true;
        if(!(whileBlackLine[LL] && whileBlackLine[RR])) break;
        manager.back(slowSpeed);
    }
    manager.stop(false);
    delay(5);
    if (whileBlackLine[LL]){
        leftPower = 0;
        rightPower = slowSpeed;
        if(!readLR[0]) rightPower *= -1;
        while (!lineSensors[L].read()) manager.write(leftPower, rightPower);
    }
    else{
        leftPower = slowSpeed;
        rightPower = 0;
        if(!readLR[1]) leftPower *= -1;
        while (!lineSensors[R].read()) manager.write(leftPower, rightPower);
    }
    manager.stop(false);
    delay(5);
}

bool Linetracer::finalJudge(){
    Serial.println("finalJudge");
    if(lineResult[LL]){
        while(lineSensors[LL].read()){
            manager.right(speed, false);
            if(lineSensors[C].read())return true;
    }
        while(!lineSensors[LL].read()){
            manager.right(-speed, false);
            if(lineSensors[C].read())return true;
        }
    }
    else if(lineResult[RR]){
        while(lineSensors[RR].read()){
            manager.left(speed, false);
            if(lineSensors[C].read())return true;
        }
            
        while(!lineSensors[RR].read()){
            manager.left(-speed, false);
            if(lineSensors[C].read())return true;
        }  
    }else if(lineResult[C]) return true;
    manager.stop(false);
    return false;
}

Linetracer::Colors Linetracer::judgeColor(){
    manager.back(slowSpeed, backLength * 3.5);
    int result = 0;
    if(colorSensors[0].read() == 'G') result++;
    if(colorSensors[1].read() == 'G') result += 2;
    manager.straight(slowSpeed, straightLength * 3.5);
    return (Linetracer::Colors)result;
}

void Linetracer::right90(){
    manager.stop(false);
    manager.straight(slowSpeed, STRAIGHT_LENGH);
    while (lineSensors[C].read())
        manager.right(slowSpeed, true);
    while (!lineSensors[C].read())
        manager.right(slowSpeed, true);
}

void Linetracer::left90(){
    manager.stop(false);
    manager.straight(slowSpeed, STRAIGHT_LENGH);
    while (lineSensors[C].read())
        manager.left(slowSpeed, true);
    while (!lineSensors[C].read())
        manager.left(slowSpeed, true);
}

const char* Linetracer::colorsToString(Linetracer::Colors color){
    switch (color){
        case WW: return "WW";
        case GW: return "GW";
        case WG: return "WG";
        case GG: return "GG";
        default: return "err";
    }
}

bool Linetracer::run(){
    for (size_t i = 0; i < 5; i++){
        lineResult[i] = lineSensors[i].read();
        blackSum += lineResult[i];
    }
    for (size_t i = 0; i < 5; i++){
        Serial.print(lineResult[i]);
        Serial.print(", ");
    }
    Serial.println("");
    //speed = tiltSensor.read()? SPEED * SPEED_ACC: SPEED;
    Serial.print("current speed: ");
    Serial.println(speed);
    // colorResult = judgeColor();
    // Serial.println(colorsToString(colorResult));

    // if(colorResult == GW)
    //     left90();
    // else if(colorResult == WG)
    //     right90();
    // else if(colorResult == GG){
    //     right90();
    //     right90();
    // }

    // これだと大分条件がゆるいし比例もどきすらもできないので、
    // あとで((lineResult[L] && lineResult[L]) || (lineResult[R] && lineResult[RR]))のブランチも作る←嘘。作らん。
    if(lineResult[L] || lineResult[R]) {
        manager.straight(slowSpeed, straightLength * 1.5);
        Serial.print("blackSum: ");
        Serial.println(blackSum);
        REN = 0;
        if(lineResult[LL]){
            while (lineSensors[LL].read()){
                manager.straight(slowSpeed);
                if(lineSensors[RR].read()){
                    Linetracer::Colors colorResult = judgeColor();
                    if(colorResult == GW)
                        left90();
                    else if(colorResult == WG)
                        right90();
                    else if(colorResult == GG){
                        right90();
                        right90();
                    }
                }
            }
        }
        if(lineResult[RR]){
            while (lineSensors[RR].read()){
                manager.straight(slowSpeed);
                if(lineSensors[LL].read()){
                    Linetracer::Colors colorResult = judgeColor();
                    if(colorResult == GW)
                        left90();
                    else if(colorResult == WG)
                        right90();
                    else if(colorResult == GG){
                        right90();
                        right90();
                    }
                }
            }
        }
        Serial.print("color: ");
        Serial.println(colorsToString(colorResult));
        if(colorResult == WW){
            manager.stop(false);
            manager.straight(slowSpeed, straightLength * 5);
            //manager.straight(slowSpeed, straightLength * 5);
            // blackSum = 0;
            // for (size_t i = 0; i < 5; i++) blackSum += lineSensors[i].read();
            // if(blackSum >= 3) manager.straight(speed, straightLength);
            // else if (lineResult[L]) // ここはlineResult[LL]の方が良いかも
            //     left90();
            // else if (lineResult[R]) // ここもlineResult[RR]の方が良いかも
            //     right90();
            // else // 何か事故が起きてるので少し下がってみる
            //     manager.back(speed, backLength);
        }
        // 正味ここらへんの条件分岐スタックうまく使えば賢く書けそうだけどまぁいいや
        // else if(colorResult == GW)
        //     left90();
        // else if(colorResult == WG)
        //     right90();
        // else if(colorResult == GG){
        //     right90();
        //     right90();
        // }
        manager.stop(false);
    }
    else if(lineResult[LL]){
        REN = 0;
        if(!finalJudge()){
            Serial.println("left 90");
            left90();
        }
    }
    else if(lineResult[RR]){
        REN = 0;
        if(!finalJudge()){
            Serial.println("right 90");
            right90();
        }
    }
    else if(lineResult[L]){
        Serial.println("L");
        REN++;
        manager.left(speed, true);
    }
    else if(lineResult[R]){
        Serial.println("R");
        REN++;
        manager.right(speed, true);
    }
    else {
        Serial.println("Straight");
        REN = 0;
        manager.straight(speed);
    }
    if(REN > THRESHOLD_REN)
        manager.straight(slowSpeed, RENlength);
    //delay(1);
    blackSum = 0;
    return true;
}
