#include "Linetracer.h"
#include "Arduino.h"
#include "Motor.h"
#include "Move.h"
Linetracer::Linetracer():
    manager(Motor(1, 2), Motor(3, 4)) {

}

void Linetracer::run(){
    for (size_t i = 0; i < 5; i++)  readLineResult[i] = phts[i].read;

    if(readLineResult[LL] || readLineResult[RR]) {  //  もし端っこが読んでいたら
        adjustment();
        
    }
}
