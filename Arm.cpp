#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"

static const float ARM_SPEED  = 0.4;

Arm::Arm(uint8_t tiltDev, 
         uint8_t grabMod, uint32_t grabChan, 
         uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2)
{
    SmoothJoystick* joy = robot->gunnerJoy;
    joy -> pushBtn(BUTTON_CLAMP_DOWN, (void*)this, &buttonHelper); //A -- open
    joy -> pushBtn(BUTTON_CLAMP_UP, (void*)this, &buttonHelper); //B -- close
    
    grabWheel = new Talon(grabMod,grabChan);
    tiltControl = new CANJaguar(tiltDev); // fake values
    clamp = new DoubleSolenoid(SolMod, SolPort1, SolPort2);
    openArm();
    isAdjusting = false;
    robot->updateRegistry.add((void*)this,&updateHelper);
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

void Arm::armButtons(unsigned int btn) 
{
    if(btn == BUTTON_CLAMP_DOWN)
    {
        closeArm();
    }
    else if (btn == BUTTON_CLAMP_UP)
    {
        openArm();
    } 
}

void Arm::update()
{
    SmoothJoystick* joy = robot->gunnerJoy;
    static int output=0;
    if(output%20==0)
    {
        printf("tilt up: %d, down: %d\n",joy->GetRawButton(BUTTON_TILT_UP),joy->GetRawButton(BUTTON_TILT_DOWN));
    }
    if (joy->GetRawButton(BUTTON_TILT_UP))
    {
        tiltUp();
    } 
    else if (joy->GetRawButton(BUTTON_TILT_DOWN))
    {
        tiltDown();
    }
    else
    {
        tiltZero();
    }
}

void Arm::buttonHelper(void* o, unsigned int btn) {
    ((Arm*)o) -> armButtons(btn);
}

void Arm::updateHelper(void* o)
{
    ((Arm*)o) -> update();
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
