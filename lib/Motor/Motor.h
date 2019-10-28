#ifndef ___Class_Motor
#define ___Class_Motor

class Motor {
private:
    int Fpin, Bpin, mode;
    void stop();

public:
    Motor(int Fpin, int Bpin);
    void write(int speed);
};

#endif
