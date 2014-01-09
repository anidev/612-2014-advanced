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
        Shift();
        ~Shift();
        void shiftGear();
private:
    Gear gear;
    DoubleSolenoid shift;
};
#endif
