#include "UltrasonicSensor.h"
#include "Arduino.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin): 
trigger(triggerPin, OUTPUT), echoPin(echoPin) {

}

double UltrasonicSensor::readDistance() {
    dis = 0;
    for (size_t i = 0; i < loopNum; i++){
        trigger.write(1);
        delayMicroseconds(10);
        trigger.write(0);
        readTime = pulseIn(echoPin, HIGH, 30000) / 2.0;
        dis += readTime * 340.29 * 100 / 1000000;
    }
    return (dis / 10);
}