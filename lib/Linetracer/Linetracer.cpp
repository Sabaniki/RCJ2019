#pragma region includes
#include "Linetracer.h"
#include "Arduino.h"
#include "PhotoReflector.h"
#include "PhotoReflector.cpp"
#include "Motor.h"
#include "Motor.cpp"
#include "Move.h"
#include "Move.cpp"
#pragma endregion

Linetracer::Linetracer():
    manager(Motor(1, 2), Motor(3, 4)) {

}

void Linetracer::adjustment(){

}

void Linetracer::run(){
    for (size_t i = 0; i < 5; i++)  readLineResult[i] = phts[i].read();

    if(readLineResult[LL] || readLineResult[RR]) {  //  もし端っこが読んでいたら
        adjustment();
    }
}
