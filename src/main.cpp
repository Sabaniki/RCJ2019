#include <Arduino.h>
#include "Linetracer.h"
#include "Linetracer.cpp"

void setup() {
	
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	auto tracer = new Linetracer();
	delay(1000);
	while(tracer->run());
	while(true/* resucue->run() */);
}