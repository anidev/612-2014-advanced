#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>

#include "SmoothJoystick.h"
#include "Sensors.h"
#include "Pneumatics.h"
#include "Motors.h"

class robot_class : public IterativeRobot
{
enum BUTTON
{
    PNEUMATICS, //pnumatics
    SENSORS, //sensors
    MOTORS //motors
};
public:
    robot_class();

    void RobotInit();

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
    
    //DerekDrive* test_drivetrain;
    SmoothJoystick* driverJoy;
    Sensors* sense;
    Motors* motors;
    Pneumatics* pneumatics;
    UpdateRegistry updateRegistry;
private:
    BUTTON button;
    int selection;
    void printStuff();
    void getButtons();
};

#endif // MAIN_H
