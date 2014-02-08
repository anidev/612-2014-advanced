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
                  CLAMP_MOD, CLAMP_PORT_1, CLAMP_PORT_2,
                  TILT_MOD_A, TILT_CHAN_A);
    
    drivetrain = new DerekDrive(SHIFT_MOD, SHIFT_CHAN_F, SHIFT_CHAN_R,
                                
                                LEFT_ENCODER_A_MOD,LEFT_ENCODER_A_CHAN, 
                                LEFT_ENCODER_B_MOD,LEFT_ENCODER_B_CHAN,
                                
                                RIGHT_ENCODER_A_MOD,RIGHT_ENCODER_A_CHAN, 
                                RIGHT_ENCODER_B_MOD,RIGHT_ENCODER_B_CHAN,
                                
                                TALON_FL_MODULE, TALON_FL_CHANNEL,
                                TALON_RL_MODULE, TALON_RL_CHANNEL,
                                TALON_FR_MODULE, TALON_FR_CHANNEL,
                                TALON_RR_MODULE, TALON_RR_CHANNEL);
    ultrasonic = new AnalogChannel(ULTRASONIC_MOD,ULTRASONIC_CHAN);
    infrared = new AnalogChannel(INFRARED_MOD,INFRARED_CHAN);

    shooter = new Shooter(SHOOTER_WD_MOD, SHOOTER_WD_CHAN,
                          INFRARED_MOD,   INFRARED_CHAN,
                          DOG_CLUTCH_MOD, DOG_CLUTCH_FCHAN, DOG_CLUTCH_RCHAN);
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{
    imgFlag = false;
    hgClose = false;
}

void robot_class::AutonomousPeriodic()
{
    pnum->pressurize(); //maintains air pressure, should be in all periodic functions  
    init_vision();
    if (!imgFlag) {
        hgClose = (engine->getHotGoal());
        imgFlag = true;
    }
    if (!hgClose) {
        drivetrain->autoTurn(90); // fake
    } else {
        shooter->shoot(); //fake ports for shooter, a bunch of stuff needs to be tweaked
        drivetrain->autoDrive(5); // fake
    }
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
    
}

void robot_class::TestPeriodic()
{
    updateRegistry.update();
    printf("ultrasonic voltage: %f, ultrasonic value: %f\n", (float)ultrasonic->GetVoltage(), (float)ultrasonic->GetValue());
    printf("infrared voltage: %f, infrared value: %f\n", (float)infrared->GetVoltage(), (float)infrared->GetValue());
}

//vision
void robot_class::init_vision() {
    std::printf("init vision\n");
    engine = new vision();
}

void robot_class::stop_vision() {
    std::printf("stop vision\n");
    if(engine!=NULL) {
        if(engine->isContinuousRunning()) {
            engine->stopContinuous();
        }
        delete engine;
        engine=NULL;
    }
}

START_ROBOT_CLASS(robot_class)
