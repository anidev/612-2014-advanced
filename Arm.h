#ifndef ARM_H
#define ARM_H

#include <CANJaguar.h>
#include <Talon.h>
//#include <Encoder.h>

class Arm
{
enum clampPosition
{
    UP,
    LOW
};
public:
    Arm(uint8_t tiltDev, uint8_t grabMod, uint32_t grabChan, uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2);
    void openArm();
    void closeArm();
    void grab(/*will have parameter based on sensor*/);
    void setAngle(float ang);
    void tiltUp();
    void tiltDown();
    void tiltZero();
    static void updateArm(void*, unsigned int);
private:
    CANJaguar* tiltControl;
    Talon* grabWheel;
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
