#ifndef ___Class_SwitchPin
#define ___Class_SwitchPin


class SwitchPin{
    private:
        DigitalPin input;
    public:
        bool read();
        int getPinNumber();
};

#endif