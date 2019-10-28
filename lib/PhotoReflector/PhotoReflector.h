#ifndef ___Class_PhtoReflector
#define ___Class_PhtoReflector
#include "DigitalPin.h"
class PhotoReflector{
private:
    DigitalPin readerPin;
    bool isBlack;

public:
    PhotoReflector(int pin);
    bool read();    // 内部でdigitalReadしてboolを返す
    bool getIsBlack();  // 前回のdigitalRead結果を返す
};

#endif