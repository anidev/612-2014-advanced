#include "main.h"
#include "612.h"
#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>

robot_class* robot=NULL;

robot_class::robot_class():
    test_gamepad(1),
    test_shifter(7,8,6,5,8,8,(void*)this),
    talon_state(0)
{
    /*
    compressor = new Relay(1,8,Relay::kForwardOnly);
    pnumSwitch =  new DigitalInput(1,8);
    */
    //test_drivetrain = new DerekDrive(new Talon(), new Talon(), new Talon(), new Talon());
    
    robot=this;
    test_talon = new Talon(1,5);
    test_gamepad.pushBtn(1,(void*)this,&changeMotor);
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
    static int output=0;
    if(output%20==0) {
        std::printf("test periodic\n");
    }
    output++;
    test_gamepad.updateSJ();
    test_shifter.update(&test_shifter);
}

void robot_class::changeMotor(void* o,unsigned int btn) {
    int state=robot->talon_state;
    if(state==0) {
        robot->test_talon->Set(1.0f);
        state=1;
    } else if(state==1) {
        robot->test_talon->Set(-1.0f);
        state=2;
    } else if(state==2) {
        robot->test_talon->Set(0.0f);
        state=0;
    }
}

START_ROBOT_CLASS(robot_class)
