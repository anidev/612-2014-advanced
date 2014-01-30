#ifndef ARM_H
#define ARM_H

#include <CANJaguar.h>
//#include <Encoder.h>

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
    void setAngle(float ang);
    void tiltUp();
    void tiltDown();
    static void updateArm(void*, unsigned int);
private:
    CANJaguar* tiltControl;
    CANJaguar* grabWheel;
    DoubleSolenoid* clamp;
    //Encoder* arm;
    bool isAdjusting;
    bool isGrabbing;
    float curAngle;
    static const float GRAB_SPEED = 0.0;
    static const float ARM_SPEED  = 0.4;
    clampPosition clampPos;
};

#endif
