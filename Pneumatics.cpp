#include "Pneumatics.h"
#include "main.h"

Pneumatics::Pneumatics()
{
    shift1 = new DoubleSolenoid(SHIFT_MOD,SHIFT_CHAN_F,SHIFT_CHAN_R);
    clamp = new DoubleSolenoid(CLAMP_MOD,CLAMP_PORT_1,CLAMP_PORT_2);
    
//     compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
//     digiSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
}

void Pneumatics::runPneumatics(int pnum)
{
    int prevPnum = 0;
//     bool isNotified = false;
    pressurize();
    unsigned long int prevVal = 0;
    if (pnum >= 0 && pnum < 10)
    {
        toggleSolenoid(shift1);
        if (prevPnum != pnum)
        {
            std::printf("Shift Solenoid\n");
        }
    }
    else if (pnum >= 10 && pnum < 20)
    {
        toggleSolenoid(clamp);
        if (prevPnum != pnum)
        {
            std::printf("Clamp Solenoid\n");
        }
    }
    else if (pnum >= 20 && pnum < 30)
    {
        if (robot->sense->pnumSwitch->Get() != prevVal)
        {
            std::printf("DigitalInput: %ld\n", robot->sense->pnumSwitch->Get()); 
        }
    }
    else if(pnum >= 30)
    {
        std::printf("MAX");
        robot->selection = 29;
    }
    prevPnum = pnum;
}
void Pneumatics::toggleSolenoid(DoubleSolenoid* sol)
{
    axis = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    if (axis > JOYSTICK_ZERO_TOLERANCE)
        sol->Set(DoubleSolenoid::kForward);
    else if (axis < JOYSTICK_ZERO_TOLERANCE*-1)
        sol->Set(DoubleSolenoid::kReverse);
}
void Pneumatics::pressurize()
{
    if (robot->sense->pnumSwitch->Get() == 0)
        robot->motors->compressor->Set(Relay::kForward);
    else
        robot->motors->compressor->Set(Relay::kOff);
}

