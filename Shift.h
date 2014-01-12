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
        static void shiftGear(void*);
        static void update(void*);
private:
    SmoothJoystick* test_gamepad_shift;
    Gear gear;
    DoubleSolenoid* shift;
    Timer timer;
};
#endif
