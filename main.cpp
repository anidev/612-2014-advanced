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

    //Fist one is for the switch, second is for the compressor
    pnum = new Pneumatics(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL, 
                          PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    
    arm = new Arm(TILT_DEV,
                  GRAB_MOD, GRAB_CHAN,
                  CLAMP_MOD, CLAMP_PORT_1, CLAMP_PORT_2);
    
    drivetrain = new DerekDrive(SHIFT_MOD, SHIFT_CHAN_F, SHIFT_CHAN_R,
                                
                                LEFT_ENCODER_A_MOD,LEFT_ENCODER_A_CHAN, 
                                LEFT_ENCODER_B_MOD,LEFT_ENCODER_B_CHAN,
                                
                                RIGHT_ENCODER_A_MOD,RIGHT_ENCODER_A_CHAN, 
                                RIGHT_ENCODER_B_MOD,RIGHT_ENCODER_B_CHAN,
                                
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
    pnum -> pressurize();
    updateRegistry.update();
    drivetrain -> doTeleOp();
    //commented out to avoid compiler warning barf
    
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
