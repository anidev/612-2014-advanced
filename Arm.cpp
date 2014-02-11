#include <DoubleSolenoid.h>
#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include "Arm.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"
#include "Controls.h"

static const float ARM_SPEED  = 1.0f;

Arm::Arm(uint8_t tiltDev, 
         uint8_t grabMod, uint32_t grabChan, 
         uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2,
         uint8_t tiltModA, uint32_t tiltChanA)
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
    
    tiltAngle = new AnalogChannel(tiltModA, tiltChanA);
    accel = new ADXL345_I2C(1);
    pitch = 0.0f;
    raw_val = 0.0f;
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
    if (joy->GetTriggerState() == TRIG_R)
    {
        tiltUp();
    } 
    else if (joy->GetTriggerState() == TRIG_L)
    {
        tiltDown();
    }
    else
    {
        tiltZero();
    }
    if (joy->GetRawButton(BUTTON_GRAB))
    {
        grab();
    }
    else
    {
        grabWheel -> Set(0.0f);
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

float Arm::voltageToDegree(float angle) {
    return angle*60;
}

void Arm::setAngle(float angle) {
    if (!isAdjusting) {
        isAdjusting = true;
    }
    float newAngle = Arm::voltageToDegree(angle); 
    float accel_x = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
    float accel_y = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
    float accel_z = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
    pitch = (atan2(accel_x, sqrt(accel_y * accel_y + accel_z * accel_z))) / PI;
    printf("%f\n", pitch);
    if (fabs(curAngle - newAngle) > VOLT_THRESH) {
        if (curAngle > newAngle) {
            tiltDown();
        } else {
            tiltUp();
        }
    } else {
        isAdjusting = false;
        tiltZero();
        return;
    }
}

double Arm::getAngle() {
    return pitch;
}

