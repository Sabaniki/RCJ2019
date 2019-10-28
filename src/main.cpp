#include <Arduino.h>
#include "DigitalPin.h"

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  auto pin = DigitalPin(13, OUTPUT);
  while (true){
    pin.write(1);
    delay(100);
    pin.write(0);
    delay(100);
  }
  
}