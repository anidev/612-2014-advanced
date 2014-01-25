#include "main.h"
#include "612.h"
#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <ADXL345_SPI.h>

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
    
    accel = new ADXL345_SPI(1,1,2,3,4);
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
    test_gamepad.updateSJ();
    test_shifter.update(&test_shifter);
    
    if(output%10==0) {
//        std::printf("beforeX ");
        double axisX=accel->GetAcceleration(ADXL345_SPI::kAxis_X);
//        std::printf("afterX ");
//        std::printf("beforeY ");
        double axisY=accel->GetAcceleration(ADXL345_SPI::kAxis_Y);
//        std::printf("afterY ");
//        std::printf("beforeZ ");
        double axisZ=accel->GetAcceleration(ADXL345_SPI::kAxis_Y);
//        std::printf("afterZ ");
//        std::printf("axes X: %f, Y: %f, Z: %f\n",axisX,axisY,axisZ);
        std::printf("Z: %f\n",axisZ);
    }
    
    output++;
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
