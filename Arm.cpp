#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "ports.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"

Arm::Arm(uint8_t tiltDev, 
         uint8_t grabMod, uint32_t grabChan, 
         uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2)
{
    SmoothJoystick* joy = robot->gunnerJoy;
    joy -> pushBtn(1, (void*)this, &updateArm); //A -- open
    joy -> pushBtn(2, (void*)this, &updateArm); //B -- close
    
    joy -> pushBtn(3, (void*)this, &updateArm); //X -- tilt up
    joy -> pushBtn(4, (void*)this, &updateArm); //Y -- tilt down
    
    grabWheel = new Talon(grabMod,grabChan); //fake values
    tiltControl = new CANJaguar(tiltDev);
    clamp = new DoubleSolenoid(SolMod, SolPort1, SolPort2);
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

void Arm::updateArm(void* o, unsigned int btn) 
{
    Arm* a = (Arm*)o;
    if(btn==2)
    {
        a->closeArm();
    }
    else if (btn==1)
    {
        a->openArm();
    } 
    else if (btn==3)
    {
        a->tiltUp();
    } 
    else if (btn==4)
    {
        a->tiltDown();
    } else {
        a->tiltZero();
    }
}

void Arm::tiltUp() 
{
    tiltControl->Set(ARM_SPEED);
}

void Arm::tiltDown() 
{
    tiltControl->Set(-ARM_SPEED);
}

void Arm::tiltZero()
{
    tiltControl->Set(0);
}
