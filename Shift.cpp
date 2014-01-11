#include "main.h"
#include <DoubleSolenoid.h>
#include "Shift.h"
#include "SmoothJoystick.h"

Shift::Shift(uint32_t forwardChan,uint32_t reverseChan, void* o):timer()
{
    robot_class* robot = (robot_class*)o;
    test_gamepad_shift = &robot->test_gamepad;
    test_gamepad_shift -> pushBtn(5, (void*)this, &shiftGear); // L1 to shift gears
    shift = new DoubleSolenoid(1,forwardChan, reverseChan);
    //make it default high gear to avoid it being bumped in between gears
    shift -> Set(DoubleSolenoid::kForward);
    timer.Start();
    gear = HIGH;
}
Shift::~Shift()
{
    
}

void Shift::update(void* o) {
    Shift* sh = (Shift*)o;
    if(sh -> timer.Get()>=0.15) {
        sh -> shift -> Set(DoubleSolenoid::kOff);
    }
}

void Shift::shiftGear(void* o)
{
    printf("========== shifting gears all dei errdei ==========\n");
    Shift* sh = (Shift*)o;
    if (sh->gear==HIGH)
    {
        sh -> shift -> Set(DoubleSolenoid::kReverse);
        sh -> gear = LOW;
    }
    else
    {
        sh -> shift -> Set(DoubleSolenoid::kForward);
        sh -> gear = HIGH;
    }
    sh -> timer.Reset();
}

