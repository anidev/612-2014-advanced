#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
#include "main.h"
#include "Shift.h"


class DerekDrive
{
public:
    DerekDrive();
    ~DerekDrive();
    void autoDrive(float,float);
    void autoRotate();
    void doTeleOp();
    void stop();
    void setSafety();
    void update(bool);
    void shift();
private:
    /*
     *  Talon frontLeft;
     *  Talon frontRight;
     *  Talon rearLeft;
     *  Talon rearRight;
     */
    float drivePower; // 1.0 Normal and 0.6 Climbing
    bool isAsync;
};
#endif
