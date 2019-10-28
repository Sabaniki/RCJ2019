#ifndef ___Class_UltrasonicSensor
#define ___Class_UltrasonicSensor
#include "DigitalPin.h"
class UltrasonicSensor {
private:
    int triggerPin, echoPin, readTime, dis;
    const int loopNum = 10;
    DigitalPin trigger;

public:
    UltrasonicSensor(int triggerPin, int echoPin);
    double readDistance();
};

#endif
