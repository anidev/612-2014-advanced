#include "main.h"
#include <DoubleSolenoid.h>
#include "Shift.h"
#include "SmoothJoystick.h"

Shift::Shift(uint32_t forwardChan,uint32_t reverseChan, void* o)
{
    robot_class* robot = (robot_class*)o;
    test_gamepad_shift = &robot->test_gamepad;
    test_gamepad_shift -> pushBtn(5, (void*)this, &shiftGear); // L1 to shift gears
    shift = new DoubleSolenoid(forwardChan, reverseChan);
    //make it default high gear to avoid it being bumped in between gears
    shift -> Set(DoubleSolenoid::kForward);
    shift -> Set(DoubleSolenoid::kOff);
    gear = HIGH;
}
Shift::~Shift()
{
    
}

void Shift::shiftGear(void* o)
{
    printf("shifting gears all dei errdei");
    Shift* sh = (Shift*)o;
    if (sh->gear==HIGH)
    {
        sh -> shift -> Set(DoubleSolenoid::kForward);
        sh -> shift -> Set(DoubleSolenoid::kOff);
        sh -> gear = HIGH;
    }
    else
    {
        sh -> shift -> Set(DoubleSolenoid::kReverse);
        sh -> shift -> Set(DoubleSolenoid::kOff);
        sh -> gear = LOW;
    }
}

