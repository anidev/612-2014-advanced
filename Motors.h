#ifndef MOTORS_H
#define MOTORS_H

#include <SpeedController.h>
#include <Talon.h>
#include <CANJaguar.h>
#include <Relay.h>

#include "ports.h"
#include "SmoothJoystick.h"
#include "Controls.h"


class Motors
{
public:
    Motors::Motors();
    void runMotor(int motor);
private:
    //SmoothJoystick* joy;
    float joy;
    float power;
    float left;
    float right;
    void drive();

    Talon* FR;
    Talon* FL;
    Talon* RR;
    Talon* RL;
    
    Talon* grabber;
    
    CANJaguar* tilt; //CANJag
    
    Relay* compressor;
};
#endif
