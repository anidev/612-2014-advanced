#include "Shooter.h"

Shooter::Shooter(uint8_t wdMod,  uint32_t wdChan,
                 uint8_t infMod, uint32_t infChan,
                 uint8_t dcMod,  uint32_t dcfChan, uint32_t dcrChan)
{
    wormDrive = new Talon(wdMod, wdChan);
    infrared  = new AnalogChannel(infMod, infChan);
    dogClutch = new DoubleSolenoid(dcMod, dcfChan, dcrChan);
}

Shooter::~Shooter()
{
    
}

void Shooter::shoot()
{
    dogClutch->Set(DoubleSolenoid::kReverse);
    rewind();
}

void Shooter::rewind()
{
    dogClutch->Set(DoubleSolenoid::kForward);
    if (infrared->GetVoltage() > 5)
        wormDrive->Set(-0.7f);
}


