#ifndef MOTORS_H
#define MOTORS_H

#include <SpeedController.h>
#include <Talon.h>
#include <CANJaguar.h>
#include <Relay.h>

class Motors
{
public:
    Motors::Motors();
    void runMotor(int motor);  
private:
    void drive();
    
    SpeedController* FR;
    SpeedController* FL;
    SpeedController* RR;
    SpeedController* RL;
    
    SpeedController* grabber;
    
    SpeedController* tilt; //CANJag
    
    Relay* compressor;
};
#endif
