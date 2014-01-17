#ifndef SHIFT_H
#define SHIFT_H


#include "main.h"
#include <DoubleSolenoid.h>
#include <Timer.h>
#include "SmoothJoystick.h"
class Shift
{
enum Gear
{
    HIGH,
    LOW
};
public:
        Shift(uint32_t,uint32_t, void*);
        ~Shift();
        void shiftGear();
        void update(void*);
        void shiftLow();
        void shiftHigh();
private:
    SmoothJoystick* test_gamepad_shift;
    Gear gear;
    DoubleSolenoid* shift;
    Timer timer;
};
#endif
