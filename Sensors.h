#ifndef SENSORS_H
#define SENSORS_H

#include <DigitalInput.h>
#include <Encoder.h>

class Sensors
{
public:
    Sensors::Sensors();
    void runSensors(int sense);
    
    DigitalInput* pnumSwitch;
    
    Encoder* left;
    Encoder* right;
private:
    //sensors
};

#endif
