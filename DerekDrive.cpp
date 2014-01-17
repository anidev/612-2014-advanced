#include "DerekDrive.h"
#include "main.h"
#include "Shift.h"

DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2,
                       uint8_t modFL,uint32_t chanFL,
                       uint8_t modRL,uint32_t chanRL,
                       uint8_t modFR,uint32_t chanFR,
                       uint8_t modRR,uint32_t chanRR,void* o)
                    :RobotDrive(new Talon(modFL,chanFL),
                                new Talon(modRL,chanRL),
                                new Talon(modFR,chanFR),
                                new Talon(modRR,chanRR))
{
    /*
    frontLeft = *fL;
    frontRight = *fR;
    rearLeft = *rL;
    rearRight = *rR;
     */
    shifter = new Shift(shift1,shift2,o);
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
void DerekDrive::shiftGear()
{
    //TODO
    shifter -> shiftGear();
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

