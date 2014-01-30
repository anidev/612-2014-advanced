#include "Phoomatics.h"
#include <Relay.h>
#include <DigitalInput.h>
#include "main.h"
#include "612.h"

Phoomatics::Phoomatics(uint8_t switchMod, uint32_t switchPort, uint8_t compMod, uint32_t compPort)
{
    pnumSwitch = new DigitalInput(switchMod, switchPort);
    compressor = new Relay(compMod, compPort, Relay::kForwardOnly);
    
    robot->updateRegistry.add(this, &updateHelper);
}

void Phoomatics::pressurize()
{
    if ((pnumSwitch->Get()) == 1)
    {
        compressor->Set(Relay::kOn);
    }
    else
    {
        compressor->Set(Relay::kOff);
    }
}

void Phoomatics::addSolenoid(double time, DoubleSolenoid* solenoid, DoubleSolenoid::Value value)
{
    Timer* timer = new Timer();
    pnumObj p;
    p.time = time;
    p.timer = timer;
    p.solenoid = solenoid;
    p.val = value;
    p.solenoid->Set(value);
    solenoids.push_back(p);
    p.timer->Start();
}

void Phoomatics::updateSolenoids()
{
    pressurize();
    for (unsigned int i = 0; i < solenoids.size();)
    {
        pnumObj p = solenoids[i];
        if (p.timer -> Get() >= p.time)
        {
            delete p.timer;
            p.solenoid->Set(DoubleSolenoid::kOff);
            solenoids.erase(solenoids.begin()+i);
        } 
        else
        {
            i++;
        }
    }
}

void Phoomatics::updateHelper(obj o) {
    ((Phoomatics*)(o))->updateSolenoids();
}
