#ifndef SHIFT_H
#define SHIFT_H


//#include "main.h"
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
        Shift(uint8_t shiftMod, uint32_t forwardChan, uint32_t reverseChan);
        ~Shift();
        void shiftGear();
        void shiftLow();
        void shiftHigh();
        static void eventHandler(void*,unsigned int);
private:
    Gear gear;
    DoubleSolenoid* shift;
    Timer timer;
};
#endif
