#include "Linetracer.h"
#include "Arduino.h"
// #include "PhotoReflector.h"
// #include "PhotoReflector.cpp"
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
        RotaryEncoder(ROTARY_ENCODER_READER_PIN, -1)
    ) {
}

inline void Linetracer::adjustment(){
    while (colorSensors[0].irradiateGreen())  // この時点で黒のラインを左のカラーセンサが読んでいたら、読まなくなるまで
        manager.write(-slowSpeed, 0);       // 左の車輪を後退

    while (colorSensors[1].irradiateGreen())  // 同様に、この時点で黒のラインを右のカラーセンサが読んでいたら、読まなくなるまで
        manager.write(0, -slowSpeed);       // 右の車輪を後退
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
        rightPower = speed;
        if(!readLR[0]) rightPower *= -1;
        while (!lineSensors[L].read()) manager.write(leftPower, rightPower);
    }
    else{
        leftPower = speed;
        rightPower = 0;
        if(!readLR[1]) leftPower *= -1;
        while (!lineSensors[R].read()) manager.write(leftPower, rightPower);
    }
    manager.stop(false);
    delay(5);
}

Linetracer::Colors Linetracer::judgeColor(){
    // adjustment();
    // newKingOfJudge();
    int result = 0;
    if(colorSensors[0].irradiateRed()) result++;
    if(colorSensors[1].irradiateRed()) result += 2;
    return (Linetracer::Colors)result;
}

void Linetracer::right90(){
    manager.stop(false);
    manager.straight(slowSpeed, 150);
    while (lineSensors[C].read())
        manager.right(slowSpeed, true);
    while (!lineSensors[C].read())
        manager.right(slowSpeed, true);
}

void Linetracer::left90(){
    manager.stop(false);
    manager.straight(slowSpeed, 150);
    while (lineSensors[C].read())
        manager.left(slowSpeed, true);
    while (!lineSensors[C].read())
        manager.left(slowSpeed, true);
}

bool Linetracer::run(){
    delay(1);
    for (size_t i = 0; i < 5; i++)  lineResult[i] = lineSensors[i].read();
    for (size_t i = 0; i < 5; i++) blackSum += lineResult[i];
    
    for (size_t i = 0; i < 5; i++){
        Serial.print(lineResult[i]);
        Serial.print(", ");
    }
    Serial.println("");

    // これだと大分条件がゆるいし比例もどきすらもできないので、
    // あとで((lineResult[L] && lineResult[L]) || (lineResult[R] && lineResult[RR]))のブランチも作る
    if(blackSum >= 3) {
        Serial.println("blackSum >= 3");
        REN = 0;
        Linetracer::Colors colorResult = judgeColor();
        Serial.print("color: ");
        Serial.println(Linetracer::Colors(colorResult));
        if(!colorResult){
            int blackSum = 0;
            for (size_t i = 0; i < 5; i++) blackSum += lineSensors[i].read();
            if(blackSum >= 3) manager.straight(speed, straightLength);
            else if (lineResult[L]) // ここはlineResult[LL]の方が良いかも
                left90();
            else if (lineResult[R]) // ここもlineResult[RR]の方が良いかも
                right90();
            else // 何か事故が起きてるので少し下がってみる
                manager.back(speed, backLength);
        }
        // 正味ここらへんの条件分岐スタックうまく使えば賢く書けそうだけどまぁいいや
        else if(colorResult == GW)
            left90();
        else if(colorResult == WG)
            right90();
        else if(colorResult == GG){
            right90();
            right90();
        }
        manager.stop(false);
    }
    if(lineResult[LL]){
        Serial.println("left 90");
        left90();
    }
    else if(lineResult[RR]){
        Serial.println("right 90");
        right90();
    }
    if(lineResult[L]){
        Serial.println("L");
        REN++;
        manager.left(speed, true);
    }
}