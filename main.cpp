#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <Ultrasonic.h>

#include "main.h"
#include "612.h"
#include "Phoomatics.h"
#include "SmoothJoystick.h"
#include "Shift.h"
#include "ports.h"


robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    shifter = new Shift(7,8);

    //Fist one is for the switch, second is for the compressor
    pnum = new Phoomatics(1,8, 1,8);
    
    robot = this;
    
    drivetrain = new DerekDrive(SHIFT_MOD_F, SHIFT_MOD_R,
                                1,1,
                                2,2,
                                3,3,
                                4,4,
                                TALON_FL_MODULE, TALON_FL_CHANNEL,
                                TALON_RL_MODULE, TALON_RL_CHANNEL,
                                TALON_FR_MODULE, TALON_FR_CHANNEL,
                                TALON_RR_MODULE, TALON_RR_CHANNEL);
    //Ultrasonic* ultrasonic = new Ultrasonic(port1, port2);
    driverJoy = new SmoothJoystick(1);
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
    //ultrasonic->SetEnabled(true);
    //ultrasonic->SetAutomaticMode(true);
}

void robot_class::TestPeriodic()
{
    pnum->pressurize();
    updateRegistry.update();
    //std::printf("ultrasonic value: %f\n", ultrasonic->GetRangeInches());
}

START_ROBOT_CLASS(robot_class)
