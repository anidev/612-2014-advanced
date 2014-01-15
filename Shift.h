#ifndef SHIFT_H
#define SHIFT_H


#include "main.h"
#include <DoubleSolenoid.h>
#include <Timer.h>
#include <DigitalInput.h>
#include <Relay.h>
#include "SmoothJoystick.h"
class Shift
{
enum Gear
{
    HIGH,
    LOW
};
public:
        Shift(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,void*);
        ~Shift();
        static void shiftGear(void*,unsigned int);
        static void update(void*);
private:
    SmoothJoystick* test_gamepad_shift;
    Gear gear1;
    Gear gear2;
    DoubleSolenoid* shift1;
    DoubleSolenoid* shift2;
    DigitalInput* pnumSwitch;
    Relay* compressor;
    Timer timer1;
    Timer timer2;
};
#endif
