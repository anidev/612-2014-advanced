#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <Ultrasonic.h>

#include "main.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "ports.h"
#include "Controls.h"


robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    robot = this;
    driverJoy = new SmoothJoystick(DRIVER_JOY_PORT);
    gunnerJoy = new SmoothJoystick(GUNNER_JOY_PORT);
    
    shifter = new Shift(SHIFT_MOD_F,SHIFT_MOD_R);

    //Fist one is for the switch, second is for the compressor
    pnum = new Pneumatics(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL, 
                          PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    
    arm = new Arm(TILT_DEV,
                  GRAB_MOD, GRAB_CHAN,
                  CLAMP_MOD, CLAMP_PORT_1, CLAMP_PORT_2);
    
    drivetrain = new DerekDrive(SHIFT_MOD_F, SHIFT_MOD_R,
                                LEFT_ENCODER_A_CHAN, LEFT_ENCODER_B_CHAN,
                                RIGHT_ENCODER_A_CHAN, RIGHT_ENCODER_B_CHAN,
                                TALON_FL_MODULE, TALON_FL_CHANNEL,
                                TALON_RL_MODULE, TALON_RL_CHANNEL,
                                TALON_FR_MODULE, TALON_FR_CHANNEL,
                                TALON_RR_MODULE, TALON_RR_CHANNEL);
    //Ultrasonic* ultrasonic = new Ultrasonic(port1, port2);
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
    updateRegistry.update();
    
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
    updateRegistry.update();
    //std::printf("ultrasonic value: %f\n", ultrasonic->GetRangeInches());
}

START_ROBOT_CLASS(robot_class)
