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
#include "KuromikaLine.h"
#include "KuromikaLine.cpp"

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
    Serial.println("right90 1");
    manager.stop(false);
    Serial.println("stop now");
    while (!lineSensors[C].read())
        manager.right(slowSpeed, true);
    Serial.println("right90 2");
    Serial.println("stop now");
    manager.stop(false);
    
}

void Linetracer::left90(){
    manager.stop(false);
    manager.straight(slowSpeed, 150);
    while (lineSensors[C].read())
        manager.left(slowSpeed, true);
    Serial.println("left90 1");
    while (!lineSensors[C].read())
        manager.left(slowSpeed, true);
    Serial.println("left90 2");
    
}

bool Linetracer::run(){
    delay(10);
    for (size_t i = 0; i < 5; i++)  lineResult[i] = lineSensors[i].read();
    Serial.println();
    for (size_t i = 0; i < 5; i++) blackSum += lineResult[i];
    
    for (size_t i = 0; i < 5; i++){
        Serial.print(lineResult[i]);
        Serial.print(", ");
    }
    Serial.println("");

    if(lineResult[LL]){
        Serial.println("LL");
        //left90();
    }
    else if(lineResult[L]){
        Serial.println("L");
        manager.left(speed, true);
    }

    if(lineResult[RR]){
        Serial.println("RR");
        //right90();
    }
    else if(lineResult[R]){
        Serial.println("R");
        manager.right(speed, true);
    }
    else if(lineResult[RR] || lineResult[R]){
        Serial.println("RR | R");
        manager.right(speed, true);
    }

    else manager.straight(speed);

    blackSum = 0;
    return true;
}
