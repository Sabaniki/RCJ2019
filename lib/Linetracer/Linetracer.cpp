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
    tiltSensor(TILT_SENSOR_READER_PIN, INPUT){
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

void Linetracer::finalJudge(unsigned int untilTime){
    double multipy = 2;
    int time = 0;
    if(lineResult[LL]){
        time = millis();
        //まっすぐ
        while(millis() - time < straightLength*multipy){
            Serial.println("straight");
            manager.straight(speed);
            if(lineSensors[RR].read()){
                colorResult =  judgeColor(millis()-time);
                return;
            }
        }
        manager.stop(false);
        //まわす
        if(lineSensors[RR].read()){
            while (manager.left(slowSpeed, false), !lineSensors[LL].read());
            colorResult = judgeColor(straightLength * multipy);
            return;
        }
        //センシングその１
        else {
            time = millis();
            while(millis() - time < untilTime){
                Serial.println("adjust");
                manager.left(-speed,true);
                if(lineSensors[C].read()){
                    manager.stop(false);
                    colorResult = judgeColor(straightLength * multipy);
                    return;
                }
            }
            //センシングその２
            time = millis();
            while (millis() - time < untilTime * 2){
                Serial.println("adjust");
                manager.left(speed,true);
                if(lineSensors[C].read()){
                    manager.stop(false);
                    colorResult = judgeColor(straightLength * multipy);
                    return;
                }
            }
            left90();
            Serial.println("final: left90 was done");
            colorResult = MV;
            return;
        }
    }
    
    else if(lineResult[RR]){
        //まっすぐ
        while(millis() - time < straightLength * multipy){
            Serial.println("straight");
            manager.straight(speed);
            if(lineSensors[LL].read()){
                colorResult =  judgeColor(millis()-time);
                return;
            }
        }
        manager.stop(false);
        //回す
        if(lineSensors[LL].read()){
            while (manager.right(slowSpeed, false), !lineSensors[RR].read());
            colorResult = judgeColor(straightLength * multipy);
            return;
        }
        else {
            //センシングその１
            time = millis();
            while (millis() - time < untilTime){
                Serial.println("adjust");
                manager.right(-speed,true);
                if(lineSensors[C].read()){
                    manager.stop(false);
                    colorResult = judgeColor(straightLength * multipy);
                    return;
                }
            }
            //センシングその２
            time = millis();
            while (millis() - time < untilTime * 2){
                Serial.println("adjust");
                manager.right(speed,true);
                if(lineSensors[C].read()){
                    manager.stop(false);
                    colorResult = judgeColor(straightLength * multipy);
                    return;
                }
            }
            right90();
            Serial.println("final: righte90 was done");
            colorResult = MV;
            return;
        }
    }
}

void Linetracer::crossJunction(){

}

void Linetracer::T_Junction(){

}

void Linetracer::avoid(){
    if(switches[0].read()){
        manager.back(slowSpeed, AVOID_BACK);
        manager.right(slowSpeed, true);
        delay(AVOID_ROTATE / 2);
        manager.straight(slowSpeed, AVOID_DISTANCE);
        manager.left(slowSpeed, true);
        delay(AVOID_ROTATE);
        while(manager.straight(slowSpeed), lineSensors[C].read());
        manager.straight(slowSpeed, straightLength * 3.5);
        manager.right(slowSpeed, true);
        delay(AVOID_ROTATE / 2);
    }

    else if(switches[1].read()){
        manager.back(slowSpeed, AVOID_BACK);
        manager.left(slowSpeed, true);
        delay(AVOID_ROTATE / 2);
        manager.straight(slowSpeed, AVOID_DISTANCE);
        manager.right(slowSpeed, true);
        delay(AVOID_ROTATE);
        while(manager.straight(slowSpeed), lineSensors[C].read());
        manager.straight(slowSpeed, straightLength * 3.5);
        manager.left(slowSpeed, true);
        delay(AVOID_ROTATE / 2);
    }
}

Linetracer::Colors Linetracer::judgeColor(int time){
    Serial.println("judge color");
    manager.back(slowSpeed, backLength * 0.8 + time);
    int result = 0;
    if(colorSensors[0].read() == 'G') result++;
    if(colorSensors[1].read() == 'G') result += 2;
    manager.straight(slowSpeed, straightLength * 3.5);
    return (Linetracer::Colors)result;
}

void Linetracer::right90(){
    manager.stop(false);
    manager.straight(slowSpeed, STRAIGHT_LENGH * 0.5);
    while (lineSensors[C].read())
        manager.right(slowSpeed, true);
    while (!lineSensors[C].read())
        manager.right(slowSpeed, true);
}

void Linetracer::left90(){
    manager.stop(false);
    manager.straight(slowSpeed, STRAIGHT_LENGH * 0.5);
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
    int GGcount = 0;
    for (size_t i = 0; i < 5; i++){
        lineResult[i] = lineSensors[i].read();
        blackSum += lineResult[i];
    }
    for (size_t i = 0; i < 5; i++){
        Serial.print(lineResult[i]);
        Serial.print(", ");
    }
    Serial.println("");
    speed = tiltSensor.read()? SPEED * SPEED_ACC: SPEED;
    Serial.print("current speed: ");
    Serial.println(speed);
    colorResult = MV;

    avoid();
    if(!(blackSum == 5)){
        //manager.straight(speed*1.5,straightLength * 2);
        //manager.back(speed*1.5,straightLength * 2);
        finalJudge(1000);
    }else{
        Serial.println("All Blacks");
    }
    Serial.println(colorsToString(colorResult));
    if(colorResult == GW){
        manager.left(speed,500);
        left90();
    }
    else if(colorResult == WG){
        manager.right(speed,500);
        right90();
    }
    else if(colorResult == GG){
        while(true){
            manager.stop(false);
        }
        if(GGcount == 0){
            manager.right(speed,100);
            right90();
            right90();
        }
        else{
            GGcount++;
            manager.back(speed,backLength*8);
        }
    }
    else if(colorResult == WW){
        manager.straight(speed,straightLength);
    }

    if(lineResult[L]){
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
