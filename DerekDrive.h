#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
//#include "main.h"

enum Gear
{
    HIGH = 1,
    LOW = 0
};

class DerekDrive : public RobotDrive 
{
    public:
        DerekDrive(SpeedController*,SpeedController*,SpeedController*,SpeedController*,void*);
        ~DerekDrive();
        void autoDrive(float,float);
        void autoRotate();
        void doTeleOp();
        void stop();
        void setSafety();
        void update(bool);
        void shift(Gear);
    private:
        /*
        Talon frontLeft;
        Talon frontRight;
        Talon rearLeft;
        Talon rearRight;
        */
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
};
#endif
