#ifndef ___Cpp_DigitalPin
#define ___Cpp_DigitalPin
#include "DigitalPin.h"
#include "Arduino.h"
SwitchPin::SwitchPin(int pin):input(pin, INPUT_PULLUP){

}

bool read(){
    return input.read
}
#endif