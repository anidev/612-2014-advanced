#include "main.h"
#include <DoubleSolenoid.h>
#include "Shift.h"

Shift::Shift(uint32_t a,uint32_t b)
{
    shift = new DoubleSolenoid(a, b);
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
    if (this->highGear())
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
bool Shift::highGear()
{
    return (gear == HIGH);
}
