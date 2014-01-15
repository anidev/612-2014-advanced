#ifndef PHOOMATICS
#define PHOOMATICS

#include <main.h>
#include <Relay.h>
#include <DigitalInput.h>

class Phoomatics
{
public:
    Phoomatics(uint8_t switchMod,uint32_t switchPort,uint8_t compMod,uint32_t compPort);
    void pressure();
private:
    DigitalInput* pnumSwitch;
    Relay* compressor;
};
#endif
