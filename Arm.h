#ifndef ARM_H
#define ARM_H

#include <CANJaguar.h>
class Arm
{
enum clampPosition
{
    UP,
    LOW
};
public:
    Arm(uint8_t tiltDev, uint8_t grabDev, uint32_t SolMod, uint32_t SolPort);
    void openArm();
    void closeArm();
    void grab(/*will have parameter based on sensor*/);
    void aim(/*this'll also have a parameter*/);
    static void update(void*, unsigned int);
private:
    CANJaguar* tiltControl;
    CANJaguar* grabWheel;
    DoubleSolenoid* clamp;
    bool isAdjusting;
    bool isGrabbing;
    static const float GRAB_SPEED = 0.0;
    clampPosition clampPos;
};

#endif
