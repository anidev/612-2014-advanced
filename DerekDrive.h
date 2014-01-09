#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
#include "main.h"
#include "Shift.h"

class DerekDrive : public RobotDrive 
{
    public:
        DerekDrive(uint32_t, uint32_t,SpeedController*,SpeedController*,SpeedController*,SpeedController*,void*);
        ~DerekDrive();
        void autoDrive(float,float);
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
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
        Shift* shifter;
};
#endif
