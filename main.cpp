#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>


#include "main.h"
#include "612.h"
#include "Phoomatics.h"
#include "SmoothJoystick.h"
#include "Shift.h"


robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    shifter = new Shift(7,8);

    //test_drivetrain = new DerekDrive(new Talon(), new Talon(), new Talon(), new Talon());

    //Fist one is for the switch, second is for the compressor
    pnum = new Phoomatics(1,8, 1,8);

    robot=this;
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{

}

void robot_class::AutonomousPeriodic()
{
    pnum->pressurize(); //maintains air pressure, should be in all periodic functions    
}

void robot_class::TeleopInit()
{

}

void robot_class::TeleopPeriodic()
{
    pnum->pressurize();
    
    /*
    float left = driverJoy->GetRawAxis(2);
    float right = driverJoy->GetRawAxis(5);
    // drive->TankDrive(left, right);
    commented out to avoid compiler warning barf
    */
}

void robot_class::TestInit()
{

}

void robot_class::TestPeriodic()
{
    pnum->pressurize();
}

START_ROBOT_CLASS(robot_class)
