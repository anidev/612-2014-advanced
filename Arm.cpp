#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"
#include "Controls.h"

static const float ARM_SPEED  = 0.4;

Arm::Arm(uint8_t tiltDev, 
         uint8_t grabMod, uint32_t grabChan, 
         uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2)
{
    SmoothJoystick* joy = robot->gunnerJoy;
    joy -> pushBtn(BUTTON_TILT_DOWN, (void*)this, &updateHelper);
    joy -> pushBtn(BUTTON_TILT_UP, (void*)this, &updateHelper);
    
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

void Arm::updateArm(unsigned int btn) 
{
    SmoothJoystick* joy = robot->gunnerJoy;
    if(btn == BUTTON_CLAMP_DOWN)
    {
        closeArm();
    }
    else if (btn == BUTTON_CLAMP_UP)
    {
        openArm();
    } 
    else if (joy->GetTriggerState() == TRIG_R)
    {
        tiltUp();
    } 
    else if (joy->GetTriggerState() == TRIG_L)
    {
        tiltDown();
    } else {
        tiltZero();
    }
}

void Arm::updateHelper(void* o, unsigned int btn) {
    ((Arm*)o) -> updateArm(btn);
}

void Arm::tiltUp() 
{
    tiltControl->Set(-ARM_SPEED);
}

void Arm::tiltDown() 
{
    tiltControl->Set(ARM_SPEED);
}

void Arm::tiltZero()
{
    tiltControl->Set(0);
}
