#include "Sensors.h"

Sensors::Sensors()
{
    pnumSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
}
void Sensors::runSensors(int sense)
{
    if (sense == 0)
        std::printf(pnumSwitch -> Get());
}