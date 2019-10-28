#include "AnalogPin.h"
#include "Arduino.h"

AnalogPin::AnalogPin(const int pin, int boundrate): pin(pin){
    if(!digitalPinHasPWM(pin)){
        if(!Serial.available())
            Serial.begin(boundrate);
        Serial.print(pin);
        Serial.println("pin is not pwm pin!");
    }
}

inline int AnalogPin::read() {
    return analogRead(pin);
}

inline void AnalogPin::write(const int power){
    analogWrite(pin, power);
}