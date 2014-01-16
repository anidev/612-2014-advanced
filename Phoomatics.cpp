#include <Relay.h>
#include <DigitalInput.h>

Phoomatics::Phoomatics(uint8_t switchMod, uint32_t switchPort, uint8_t compMod, uint32_t compPort)
{
    pnumSwitch = new DigitalInput(switchMod, switchPort);
    compressor = new Relay(compMod, compPort, kForwardOnly);
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
