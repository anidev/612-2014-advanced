#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <AnalogChannel.h>

#include "SmoothJoystick.h"
#include "Shift.h"
#include "Pneumatics.h"
#include "DerekDrive.h"
#include "Arm.h"
#include "Shooter.h"

#include "UpdateRegistry.h"

#include "vision/vision.h"

#include "DataLogger.h"


class robot_class : public IterativeRobot
{
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
    
    void init_vision();
    void stop_vision();
    
    //DerekDrive* test_drivetrain;
    SmoothJoystick* driverJoy;
    SmoothJoystick* gunnerJoy;
    Shift* shifter;

    Arm* arm;
    
    DerekDrive* drivetrain;
    
    UpdateRegistry updateRegistry;
    Pneumatics* pnum;
    
    AnalogChannel* ultrasonic;
    AnalogChannel* infrared;
    
    vision* engine;
    
    Shooter* shooter;
    
    DataLogger* datalogger;
    
private:
    //autonomous flags
    bool imgFlag;
    bool hgClose;
    //task booleans
    bool shooting;
    bool turning;
    bool driving;
};

#endif // MAIN_H
