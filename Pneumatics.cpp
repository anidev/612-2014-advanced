#include "Pneumatics.h"

Pneumatics::Pneumatics()
{
    shift1 = new DoubleSolenoid(SHIFT_MOD,SHIFT_CHAN_F,SHIFT_CHAN_R);
    
    clamp = new DoubleSolenoid(CLAMP_MOD,CLAMP_PORT_1,CLAMP_PORT_2);
}

void Pneumatics::runPneumatics(int pnum)
{
    if (pnum = 0)
        toggleSolenoid();
    else if (pnum == 1)
        toggleSolenoid();
}
bool Pneumatics::toggleSolenoid()
{
    return true;
}
