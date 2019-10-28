#ifndef ___Class_AnalogPin
#define ___Class_AnalogPin

class AnalogPin{
private:
    int pin;

public:
    AnalogPin(const int pin, int boundrate = 9600);
    int read();
    void write(const int power);
};

#endif
