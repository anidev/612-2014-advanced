#include "DerekDrive.h"
#include "main.h"
#include "Shift.h"

/* Talons can be implemented after we make ports
 * 
 * 
 * 
 * 
 */


DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2)
{
    /*
     *   frontLeft = *fL;
     *   frontRight = *fR;
     *   rearLeft = *rL;
     *   rearRight = *rR;
     */
    //make shifter object
    shifter = new Shift(shift1,shift2); //Check ports here
    isAsync = false;
    //robot_class* robot = (robot_class*)o;
    drivePower = 1.0f;
}

DerekDrive::~DerekDrive()
{
    
}
void DerekDrive::autoDrive(float left, float right) 
{
    /*
     *   frontLeft.Set(1.0f);
     *   frontRight.Set(1.0f);
     *   rearLeft.Set(1.0f);
     *   rearRight.Set(1.0f);
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
void DerekDrive::shift()
{
    //TODO
//shift
}
void DerekDrive::stop()
{
    /*
     *   frontLeft.Disable();
     *   frontRight.Disable();
     *   rearLeft.Disable();
     *   rearRight.Disable();
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
