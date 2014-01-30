#ifndef PHOOMATICS
#define PHOOMATICS

#include <Relay.h>
#include <DigitalInput.h>
#include <Timer.h>
#include <DoubleSolenoid.h>

#include <vector>

const double waitTime = 0.15;

struct pnumObj
{
    double time;
    Timer* timer;
    DoubleSolenoid* solenoid;
    DoubleSolenoid::Value val;
};

class Phoomatics
{
public:
    Phoomatics(uint8_t switchMod,uint32_t switchPort,uint8_t compMod,uint32_t compPort);
    void pressurize();
    void addSolenoid(double, DoubleSolenoid*, DoubleSolenoid::Value);
    void updateSolenoids();
    
    typedef void* obj;
    typedef void(*funcName)(obj);
    static void updateHelper(obj);
    
private:
    DigitalInput* pnumSwitch;
    Relay* compressor;
    std::vector<pnumObj> solenoids;
};
#endif
