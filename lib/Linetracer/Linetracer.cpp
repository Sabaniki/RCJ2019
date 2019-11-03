#pragma region includes
#include "Linetracer.h"
#include "Arduino.h"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "Motor.h"
#include "Motor.cpp"
#include "Move.h"
#include "Move.cpp"
#include "ColorSensor.h"
#include "ColorSensor.cpp"
#pragma endregion

Linetracer::Linetracer():
    manager(Motor(1, 2), Motor(3, 4)) {

}

inline void Linetracer::adjustment(){
    while (colorSensors[0].irradiateGreen())  // この時点で黒のラインを左のカラーセンサが読んでいたら、読まなくなるまで
        manager.write(-slowSpeed, 0);       // 左の車輪を後退

    while (colorSensors[1].irradiateGreen())  // 同様に、この時点で黒のラインを右のカラーセンサが読んでいたら、読まなくなるまで
        manager.write(0, -slowSpeed);       // 右の車輪を後退
}

Linetracer::Colors Linetracer::judgeColor(){
    adjustment();
    int result = 0;
    if(colorSensors[0].irradiateRed()) result++;
    if(colorSensors[1].irradiateRed()) result += 2;
    return (Linetracer::Colors)result;
}

void Linetracer::right90(){
    manager.stop(false);
    while (phts[C].read())
        manager.right(slowSpeed, true);
    while (!phts[C].read())
        manager.right(slowSpeed, true);
}

void Linetracer::left90(){
    manager.stop(false);
    while (phts[C].read())
        manager.left(slowSpeed, true);
    while (!phts[C].read())
        manager.left(slowSpeed, true);
}

void Linetracer::run(){
    for (size_t i = 0; i < 5; i++)  lineResult[i] = phts[i].read();

    // これだと大分条件がゆるいし比例もどきすらもできないので、
    // あとで((lineResult[L] && lineResult[L]) || (lineResult[R] && lineResult[RR]))のブランチも作る
    if(lineResult[LL] || lineResult[RR]) {
        REN = 0;
        Linetracer::Colors colorResult = judgeColor();
        if(!colorResult){
            int blackSum = 0;
            for (size_t i = 0; i < 5; i++) blackSum += lineResult[i];
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
    }
    if(lineResult[L]){
        REN++;
        manager.left(speed, true);
    }
    if(lineResult[R]){
        REN++;
        manager.right(speed, true);
    }
    else {
        REN = 0;
        manager.straight(speed);
    }
    if(REN > 50)
        manager.straight(slowSpeed, RENlength);
}
