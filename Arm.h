#ifndef ARM_H
#define ARM_H

#include <CANJaguar.h>
#include <Jaguar.h>
#include <Talon.h>
#include <AnalogChannel.h>
#include <ADXL345_I2C.h>

#include <cmath>

static const float PI = atan(1) * 4;

class Arm
{

enum clampPosition
{
    UP,
    LOW
};

public:
    Arm(uint8_t tiltDev, 
        uint8_t grabMod, uint32_t grabChan, 
        uint8_t SolMod, uint32_t SolPort1, uint32_t SolPort2,
        uint8_t tiltModA, uint32_t tiltChanA);
    void openArm();
    void closeArm();
    void grab(/*will have parameter based on sensor*/);
    void setAngle(float angle); //works for periodic

    void tiltUp();
    void tiltDown();
    void tiltZero();
    void armButtons(unsigned int);
    void update();
    static void buttonHelper(void*, unsigned int);
    static void updateHelper(void*);
    static float voltageToDegree(float);
    double getAngle();
private:
    CANJaguar* tiltControl;
    Talon* grabWheel;
    DoubleSolenoid* clamp;
    //Encoder* arm;
    bool isAdjusting;
    bool isGrabbing;
    float curAngle;
    static const float GRAB_SPEED = 0.5f;
    static const float VOLT_THRESH = 0.1;
    clampPosition clampPos;
    
    AnalogChannel* tiltAngle;
    ADXL345_I2C* accel;
    float pitch;
    float raw_val;
    
    double accel_values[3];
};

#endif
