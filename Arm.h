#ifndef ARM_H
#define ARM_H

#include <CANJaguar.h>
#include <Jaguar.h>
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
    void setAngle(float ang); //works for periodic
    void tiltUp();
    void tiltDown();
    void tiltZero();
    void armButtons(unsigned int);
    void update();
    static void buttonHelper(void*, unsigned int);
    static void updateHelper(void*);
private:
    CANJaguar* tiltControl;
    Talon* grabWheel;
    DoubleSolenoid* clamp;
    //Encoder* arm;
    bool isAdjusting;
    bool isGrabbing;
    float curAngle;
    static const float GRAB_SPEED = 0.5f;
    clampPosition clampPos;
};

#endif
