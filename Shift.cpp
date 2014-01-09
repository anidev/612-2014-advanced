#include "main.h"
#include <DoubleSolenoid.h>

Shift::Shift(uint32_t shift1, uint32_t shift2)
{
    shift = new DoubleSolenoid(shift1,shift2);
    //make it default high gear to avoid it being bumped in between gears
    shift -> Set(DoubleSolenoid::kForward);
    shift -> Set(DoubleSolenoid::kOff);
    gear = HIGH;
}
Shift::~Shift()
{
    
}

void Shift::shiftGear()
{
    if (gear == LOW)
    {
        shift -> Set(DoubleSolenoid::kForward);
        shift -> Set(DoubleSolenoid::kOff);
        gear = HIGH;
    }
    else
    {
        shift -> Set(DoubleSolenoid::kReverse);
        shift -> Set(DoubleSolenoid::kOff);
        gear = Low;
    }
}
bool highGear()
{
    if (gear == HIGH)
        return true;
    else
        return false;
}
