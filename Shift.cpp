#include "main.h"
#include <DoubleSolenoid.h>
#include "Shift.h"

Shift::Shift(uint32_t,uint32_t)
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
    if (this.highGear())
    {
        shift -> Set(DoubleSolenoid::kForward);
        shift -> Set(DoubleSolenoid::kOff);
        gear = HIGH;
    }
    else
    {
        shift -> Set(DoubleSolenoid::kReverse);
        shift -> Set(DoubleSolenoid::kOff);
        gear = LOW;
    }
}
bool highGear()
{
    return (gear == HIGH);
}
