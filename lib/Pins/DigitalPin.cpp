#include "DigitalPin.h"
#include "Arduino.h"

DigitalPin::DigitalPin(int pin, int IO_Mode): pin(pin), IO_Mode(IO_Mode){
    pinMode(pin, IO_Mode);
    digitalWrite(pin, LOW);
}

inline bool DigitalPin::read(){
    return digitalRead(pin);
}

inline void DigitalPin::write(bool mode){
    digitalWrite(pin, mode);
}