#ifndef SHIFT_H
#define SHIFT_H


#include "main.h"
#include <DoubleSolenoid.h>
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
        static bool highGear;
private:
    SmoothJoystick* test_gamepad_shift;
    Gear gear;
    DoubleSolenoid* shift;
};
#endif
