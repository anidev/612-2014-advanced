#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
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
        DerekDrive::DerekDrive(uint8_t shiftMod, uint32_t shift1, uint32_t shift2,
                               //left encoders
                               uint8_t LAModF, uint32_t LAChanR,
                               uint8_t LBModF, uint32_t LBChanR,
                               //right encoders
                               uint8_t RAModF, uint32_t RAChanR,
                               uint8_t RBModF, uint32_t RBChanR,
                               //talons
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
        static void update(void*);
        void shiftGear();
    private:
        /*
        SpeedController frontLeft;
        SpeedController frontRight;
        SpeedController rearLeft;
        SpeedController rearRight;
        */
        bool encoderState;
        Encoder* encoderR;
        Encoder* encoderL;
        float encoderDistance(side s);
        void startEncoders();
        void stopEncoders();
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
        Shift* shifter;
        
        SmoothJoystick* driver;
};
#endif
