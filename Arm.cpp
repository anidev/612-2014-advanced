#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "ports.h"

Arm::Arm(uint8_t tiltDev, uint8_t grabDev, uint32_t SolMod, uint32_t SolPort)
{
    grabWheel = new CANJaguar(grabDev);
    tiltControl = new CANJaguar(tiltDev);
    clamp = new DoubleSolenoid(SolMod, SolPort);
    openArm();
    isAdjusting = false;
}
void Arm::openArm()
{
    clamp -> Set(DoubleSolenoid::kForward);
    clampPos = UP;
}
void Arm::closeArm()
{
    clamp -> Set(DoubleSolenoid::kReverse);
    clampPos = LOW;
}
void Arm::aim(/*enter parameter here*/)
{
    isAdjusting = true;
    //Adjust to whatever value is given
}
void Arm::grab()
{
    //make CANJaguar move
    grabWheel -> Set(GRAB_SPEED);
}

