#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "ports.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"

Arm::Arm(uint8_t tiltDev, uint8_t grabDev, uint32_t SolMod, uint32_t SolPort)
{
    SmoothJoystick* joy = robot->driverJoy;
    joy -> pushBtn(1, (void*)this, &updateArm); //A -- open
    joy -> pushBtn(2, (void*)this, &updateArm); //B -- close
    
    joy -> pushBtn(3, (void*)this, &updateArm); // -- open
    joy -> pushBtn(4, (void*)this, &updateArm); //B -- close
    
    grabWheel = new CANJaguar(grabDev);
    tiltControl = new CANJaguar(tiltDev);
    clamp = new DoubleSolenoid(SolMod, SolPort);
    openArm();
    isAdjusting = false;
}
void Arm::openArm()
{
    //clamp -> Set(DoubleSolenoid::kForward);
    robot->pnum->addSolenoid(waitTime, clamp, DoubleSolenoid::kForward);
    clampPos = UP;
}
void Arm::closeArm()
{
    //clamp -> Set(DoubleSolenoid::kReverse);
    robot->pnum->addSolenoid(waitTime, clamp, DoubleSolenoid::kReverse);
    clampPos = LOW;
}
void Arm::setAngle(float ang)
{
    
    isAdjusting = true;
    //Adjust to whatever value is given
}
void Arm::grab()
{
    //make CANJaguar move
    grabWheel -> Set(GRAB_SPEED);
}

void Arm::updateArm(void* o, unsigned int btn) {
    Arm* a = (Arm*)o;
    if(btn==2) {
        a->closeArm();
    } else {
        a->openArm();
    }
}

void Arm::tiltUp() {
    tiltControl->Set(ARM_SPEED);
}

void Arm::tiltDown() {
    tiltControl->Set(-ARM_SPEED);
}
