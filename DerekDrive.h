#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
#include "main.h"
#include "Shift.h"
#include <Encoder.h>
#include "SmoothJoystick.h"

enum side
{
    RIGHT,
    LEFT
};

class DerekDrive : public RobotDrive 
{
    public:
        DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2,
                               uint32_t modEncFRA, uint32_t chanEncFRA,
                               uint32_t modEncFRB, uint32_t chanEncFRB,
                               uint32_t modEncFLA, uint32_t chanEncFLA,
                               uint32_t modEncFLB, uint32_t chanEncFLB,
                               uint32_t modEncRRA, uint32_t chanEncRRA,
                               uint32_t modEncRRB, uint32_t chanEncRRB,
                               uint32_t modEncRLA, uint32_t chanEncRLA,
                               uint32_t modEncRLB, uint32_t chanEncRLB,
                               uint8_t modFL,uint32_t chanFL,
                               uint8_t modRL,uint32_t chanRL,
                               uint8_t modFR,uint32_t chanFR,
                               uint8_t modRR,uint32_t chanRR);
        ~DerekDrive();
        void autoDrive(float);
        void autoRotate();
        void doTeleOp();
        void stop();
        void setSafety();
        void update(bool);
        void shiftGear();
    private:
        /*
        SpeedController frontLeft;
        SpeedController frontRight;
        SpeedController rearLeft;
        SpeedController rearRight;
        */
        bool encoderState;
        Encoder* encoderFR;
        Encoder* encoderFL;
        Encoder* encoderRR;
        Encoder* encoderRL;
        float encoderDistance(side s);
        void startEncoders();
        void stopEncoders();
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
        Shift* shifter;
        
        SmoothJoystick* driver;
};
#endif
