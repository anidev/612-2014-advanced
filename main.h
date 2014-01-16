#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <Talon.h>
#include "SmoothJoystick.h"
#include "Shift.h"

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
    
    //DerekDrive* test_drivetrain;
    Joystick* driverJoy;
    Joystick* gunnerJoy;
    SmoothJoystick test_gamepad;
    Shift test_shifter;
    Talon* test_talon;
    int talon_state;
    
    static void changeMotor(void*,unsigned int);
private:
    //Relay* compressor;
    //DigitalInput* pnumSwitch;
};

#endif // MAIN_H
