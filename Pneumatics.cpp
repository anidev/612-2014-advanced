#include <Relay.h>
#include <DigitalInput.h>
#include "main.h"
#include "612.h"
#include "Pneumatics.h"

Pneumatics::Pneumatics(uint8_t switchMod, uint32_t switchPort, uint8_t compMod, uint32_t compPort)
{
    pnumSwitch = new DigitalInput(switchMod, switchPort);
    compressor = new Relay(compMod, compPort, Relay::kForwardOnly);
    
    robot->updateRegistry.add(this, &updateHelper);
}

void Pneumatics::pressurize()
{
    Relay::Value val = ((pnumSwitch->Get() == 0) ? Relay::kForward : Relay::kOff);
    compressor->Set(val);
    /*
    if ((pnumSwitch->Get()) == 0)
    {
        compressor->Set(Relay::kForward);
    }
    else
    {
        compressor->Set(Relay::kOff);
    }
    */
}

void Pneumatics::addSolenoid(double time, DoubleSolenoid* solenoid, DoubleSolenoid::Value value)
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

void Pneumatics::updateSolenoids()
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

void Pneumatics::updateHelper(obj o) 
{
    ((Pneumatics*)(o))->updateSolenoids();
}
