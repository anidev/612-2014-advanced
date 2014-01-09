#include "main.h"
#include <DoubleSolenoid.h>

Shift::Shift(int a, int b)
{
    shift = new DoubleSolenoid(a,b);
    //make it default high gear to avoid it being bumped in between gears
    shift -> Set(DoubleSolenoid::kForward);
    shift -> Set(DoubleSolenoid::kOff);
    Gear gear = HIGH;
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
Gear getGear()
{
    return gear;
}
