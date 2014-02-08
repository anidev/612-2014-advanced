#ifndef SHOOTER_H
#define SHOOTER_H

#include <Talon.h>
#include <AnalogChannel.h>
#include <DoubleSolenoid.h>

class Shooter {
public:
    Shooter(uint8_t, uint32_t,
            uint8_t, uint32_t,
            uint8_t dcMod,  uint32_t dcfChan, uint32_t dcrChan);
    ~Shooter();
    void shoot();
    void rewind();
private:
    Talon* wormDrive;
    AnalogChannel* infrared;
    DoubleSolenoid* dogClutch;
};

#endif

