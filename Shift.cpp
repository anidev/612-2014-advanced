#include "main.h"
#include <DoubleSolenoid.h>
#include "Shift.h"
#include "SmoothJoystick.h"
#include "Controls.h"

Shift::Shift(uint32_t forwardChan,uint32_t reverseChan, void* o):timer()
{
    robot_class* robot = (robot_class*)o;
    test_gamepad_shift = &robot->test_gamepad;
    test_gamepad_shift -> pushBtn(SHIFT_LOW, (void*)this, &eventHandler);
    test_gamepad_shift -> pushBtn(SHIFT_HIGH, (void*)this, &eventHandler);
    shift = new DoubleSolenoid(1,forwardChan, reverseChan);
    //make it default high gear to avoid it being bumped in between gears
    shift -> Set(DoubleSolenoid::kForward);
    timer.Start();
    gear = HIGH;
}
Shift::~Shift()
{
    
}

void Shift::eventHandler(void* o,unsigned int btn) {
    Shift* sh = (Shift*)o;
    if(btn==SHIFT_LOW) {
        sh->shiftLow();
    } else {
        sh->shiftHigh();
    }
}

void Shift::update(void* o) 
{
    Shift* sh = (Shift*)o;
    if(sh -> timer.Get()>=0.15) 
    {
        sh -> shift -> Set(DoubleSolenoid::kOff);
    }
}

void Shift::shiftGear()
{
    printf("========== shifting gears all dei errdei ==========\n");
    if (gear==HIGH)
    {
        shiftHigh();
    }
    else
    {
        shiftLow();
    }
    timer.Reset();
}
void Shift::shiftLow()
{
    shift -> Set(DoubleSolenoid::kReverse);
    gear = LOW;
}
void Shift::shiftHigh()
{
    shift -> Set(DoubleSolenoid::kForward);
    gear = HIGH;
}

