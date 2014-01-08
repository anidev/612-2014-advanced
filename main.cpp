#include "main.h"
#include "612.h"

robot_class* robot=NULL;

robot_class::robot_class()
{
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
}

START_ROBOT_CLASS(robot_class)
