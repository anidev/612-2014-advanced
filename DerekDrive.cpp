#include "DerekDrive.h"
//#include "main.h"

DerekDrive::DerekDrive(SpeedController* fL,SpeedController* rL,SpeedController* fR,SpeedController* rR,void* o) : RobotDrive(fL,rL,fR,rR)
{
    /*
    frontLeft = *fL;
    frontRight = *fR;
    rearLeft = *rL;
    rearRight = *rR;
    */
    isAsync = false;
    //robot_class* robot = (robot_class*)o;
    drivePower = 1.0;
    //shift LOW (or high, but we need to have a default as seen from last year)
}
    
DerekDrive::~DerekDrive()
{

}
void DerekDrive::autoDrive(float left, float right) 
{
    /*
    frontLeft.Set(1.0f);
    frontRight.Set(1.0f);
    rearLeft.Set(1.0f);
    rearRight.Set(1.0f);
    */
}
void DerekDrive::autoRotate()
{
    //TODO
}
void DerekDrive::doTeleOp()
{
    //do controls
    //TODO
}
void DerekDrive::shift(Gear g)
{
    //TODO
    if (g == HIGH)
    {
        //shift LOW
        g = LOW;
    }
    else 
    {
        //shift HIGH
        g = HIGH;
    }
}
void DerekDrive::stop()
{
    /*
    frontLeft.Disable();
    frontRight.Disable();
    rearLeft.Disable();
    rearRight.Disable();
    */
    //set jags to 0,0
}
void DerekDrive::setSafety()
{
    //TODO
}
void DerekDrive::update(bool mode)
{
    //TODO
}
