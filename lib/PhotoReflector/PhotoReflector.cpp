#include "PhotoReflector.h"
#include "DigitalPin.h"
#include "Arduino.h"

PhotoReflector::PhotoReflector(int pin): readerPin(pin, INPUT_PULLUP), isBlack(false){

}

inline bool PhotoReflector::read(){
    isBlack = readerPin.read();
    return isBlack;
}

inline bool PhotoReflector::getIsBlack(){
    return isBlack;
}