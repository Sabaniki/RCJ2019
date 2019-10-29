#include <Arduino.h>
#include "AnalogPin.h"
#include "AnalogPin.cpp"

void setup() {
	// put your setup code here, to run once:
}

void loop() {
	auto led = AnalogPin(13);
	for (size_t i = 0; i < 200; i++){
		led.write(i);
		delay(100);
	}
}