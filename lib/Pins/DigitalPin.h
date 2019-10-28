#ifndef ___Class_DigitalPin
#define ___Class_DigitalPin

class DigitalPin{
private:
    int pin;
    int IO_Mode;

public:
    DigitalPin(int pin, int IO_Mode);
    bool read();
    void write(const bool mode);
};

#endif