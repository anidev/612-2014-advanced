#ifndef Pneumatics_H
#define Pneumatics_H

#include <DoubleSolenoid.h>
#include <Timer.h>

#include "ports.h"

class Pneumatics
{
public:
    Pneumatics::Pneumatics();
    void runPneumatics(int pnum);
private:
    bool toggleSolenoid();
    DoubleSolenoid* shift1;
    //DoubleSolenoid* shift2;
    
    DoubleSolenoid* clamp;
    
    Timer* time;
};

#endif
