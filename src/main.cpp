#include <Arduino.h>
#include "Linetracer.h"
#include "Linetracer.cpp"

void setup() {
	// put your setup code here, to run once:
}

void loop() {
	auto tracer = new Linetracer();
	while(true) tracer->run();
}