#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>


#include "main.h"
#include "612.h"
#include "Phoomatics.h"


robot_class* robot=NULL;

robot_class::robot_class():
    test_gamepad(1),
    test_shifter(7,8,(void*)this)
{
    //test_drivetrain = new DerekDrive(new Talon(), new Talon(), new Talon(), new Talon());
    pnum = new Phoomatics(1,8, 1,8);
    //Fist one is for the switch, second is for the compressor
    robot=this;
}

void robot_class::RobotInit()
{
    /*
    driverJoy = new Joystick(1);
    gunnerJoy = new Joystick(2);
    Commented out to compiler warning barf
    */
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{
    pnum->pressure(); //maintains air pressure, should be in all periodic functions
}

void robot_class::AutonomousPeriodic()
{
    
}

void robot_class::TeleopInit()
{

}

void robot_class::TeleopPeriodic()
{
    pnum->pressure();
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
    pnum->pressure();
}

START_ROBOT_CLASS(robot_class)
