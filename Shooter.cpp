#include "612.h"
#include "main.h"

#include "Shooter.h"

Shooter::Shooter(uint8_t wdMod,  uint32_t wdChan,
                 uint8_t infMod, uint32_t infChan,
                 uint8_t dcMod,  uint32_t dcfChan, uint32_t dcrChan)
{
    wormDrive = new Talon(wdMod, wdChan);
    infrared  = new AnalogChannel(infMod, infChan);
    dogClutch = new DoubleSolenoid(dcMod, dcfChan, dcrChan);
    clutchSet = (dogClutch -> Get() == DoubleSolenoid::kForward);
    
    SmoothJoystick* joy = robot->driverJoy;
    joy -> pushBtn(BUTTON_LEFT_JOY_CLICK, (void*)this, &buttonHandler); //we need to change these
    joy -> pushBtn(BUTTON_RIGHT_JOY_CLICK, (void*)this, &buttonHandler); // we need to change these
    
    //we'll need to add functions here to the button registry as well
}

Shooter::~Shooter()
{
    
}

bool Shooter::shoot()
{
    if (clutchSet) {
        robot->pnum->addSolenoid(0.15, dogClutch, DoubleSolenoid::kReverse);
        clutchSet = false;
    }
    rewind();
    return (!clutchSet);
}

void Shooter::rewind()
{
    if (infrared->GetVoltage() > 5) { // fake voltage
        wormDrive->Set(-0.7f); //fake power
    } else if (!clutchSet){
        robot->pnum->addSolenoid(0.15, dogClutch, DoubleSolenoid::kForward);
        clutchSet = true;
        return;
    } else {
        return;
    }
}

void Shooter::buttonHandler(void* obj, unsigned int btn) {
    Shooter* shooter = (Shooter*)obj;
    if (btn == BUTTON_LEFT_JOY_CLICK) {
        shooter->shoot();
    } else if (btn == BUTTON_RIGHT_JOY_CLICK) {
        shooter->rewind();
    }
}

