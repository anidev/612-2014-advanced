#include "main.h"
#include <DoubleSolenoid.h>
#include <Relay.h>
#include "Shift.h"
#include "SmoothJoystick.h"

Shift::Shift(uint32_t forwardChan1,uint32_t reverseChan1, uint32_t forwardChan2,uint32_t reverseChan2, uint32_t switchChan, uint32_t compressorChan, void* o):timer1(),timer2()
{
    robot_class* robot = (robot_class*)o;
    test_gamepad_shift = &robot->test_gamepad;
    test_gamepad_shift -> pushBtn(5, (void*)this, &shiftGear); // L1 to shift gears
    test_gamepad_shift -> pushBtn(6, (void*)this, &shiftGear); // L1 to shift gears
    pnumSwitch = new DigitalInput(1,switchChan);
    compressor = new Relay(1,compressorChan,Relay::kForwardOnly);
    shift1 = new DoubleSolenoid(1,forwardChan1, reverseChan1);
    shift2 = new DoubleSolenoid(1,forwardChan2, reverseChan2);
    //make it default high gear to avoid it being bumped in between gears
    shift1 -> Set(DoubleSolenoid::kForward);
    shift2 -> Set(DoubleSolenoid::kForward);
    timer1.Start();
    timer2.Start();
    gear1 = HIGH;
    gear2 = HIGH;
}
Shift::~Shift()
{
    
}

void Shift::update(void* o) {
    Shift* sh = (Shift*)o;
    if(sh -> timer1.Get()>=0.15) {
        sh -> shift1 -> Set(DoubleSolenoid::kOff);
    }
    if(sh -> timer2.Get()>=0.15) {
        sh -> shift2 -> Set(DoubleSolenoid::kOff);
    }
    if (sh->pnumSwitch->Get() == 1)
        sh->compressor->Set(Relay::kOff);
    else
        sh->compressor->Set(Relay::kForward);
}

void Shift::shiftGear(void* o,unsigned int btn)
{
    printf("shifting buttn %d\n",btn);
    Shift* sh = (Shift*)o;
    if(btn==5) {
        if (sh->gear1==HIGH)
        {
            sh -> shift1 -> Set(DoubleSolenoid::kReverse);
            sh -> gear1 = LOW;
            sh -> timer1.Reset();
        }
        else
        {
            sh -> shift1 -> Set(DoubleSolenoid::kForward);
            sh -> gear1 = HIGH;
            sh -> timer1.Reset();
        }
    } else if(btn==6) {
        if (sh->gear2==HIGH)
        {
            sh -> shift2 -> Set(DoubleSolenoid::kReverse);
            sh -> gear2 = LOW;
            sh -> timer2.Reset();
        }
        else
        {
            sh -> shift2 -> Set(DoubleSolenoid::kForward);
            sh -> gear2 = HIGH;
            sh -> timer2.Reset();
        }
    }
}

