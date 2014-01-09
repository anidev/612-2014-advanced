#ifndef SHIFT_H
#define SHIFT_H


#include "main.h"
#include <DoubleSolenoid.h>
class Shift
{
enum Gear
{
    HIGH,
    LOW
};
public:
        Shift(uint32_t,uint32_t);
        ~Shift();
        void shiftGear();
        bool highGear();
private:
    Gear gear;
    DoubleSolenoid* shift;
};
#endif
