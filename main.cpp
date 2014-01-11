#include "main.h"
#include "612.h"
//#include <Relay.h>
//#include <DigitalInput.h>

robot_class* robot=NULL;

robot_class::robot_class():
    test_gamepad(1),
    test_shifter(7,8,(void*)this)
{
    /*
    compressor = new Relay(1,8,Relay::kForwardOnly);
    pnumSwitch =  new DigitalInput(1,2);
    */
    //test_drivetrain = new DerekDrive(new Talon(), new Talon(), new Talon(), new Talon());
    
    robot=this;
}

void robot_class::RobotInit()
{
    
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
}

void robot_class::TeleopInit()
{
}

void robot_class::TeleopPeriodic()
{
}

void robot_class::TestInit()
{
    
}

void robot_class::TestPeriodic()
{
    /*
    if (pnumSwitch->Get() == 1)
        compressor.Set(kForward);
    else
        compressor.Set(kOff);
    */
    //printf("does test even run?\n");
    test_gamepad.updateSJ();
    test_shifter.update(&test_shifter);
}

START_ROBOT_CLASS(robot_class)
