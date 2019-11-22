#include <Arduino.h>
#include "Linetracer.h"
#include "Linetracer.cpp"

void setup() {
	Serial.begin(9600);
}

void loop() {
	auto tracer = new Linetracer();
	delay(1000);
	while(tracer->run());
	while(true/* resucue->run() */);
}