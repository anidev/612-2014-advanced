#include "DerekDrive.h"
#include "main.h"
#include "Shift.h"
#include "612.h"

DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2,
                       uint32_t modEncA, uint32_t chanEncA,
                       uint32_t modEncB, uint32_t chanEncB,
                       uint8_t modFL,uint32_t chanFL,
                       uint8_t modRL,uint32_t chanRL,
                       uint8_t modFR,uint32_t chanFR,
                       uint8_t modRR,uint32_t chanRR)
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
    encoderState = false;
    encoder = new Encoder(modEncA, chanEncA, modEncB, chanEncB);
    encoder->SetDistancePerPulse(0.015);
    shifter = new Shift(shift1,shift2);
    isAsync = false;
    //robot_class* robot = (robot_class*)o;
    drivePower = 1.0;
    //shift LOW (or high, but we need to have a default as seen from last year)
    driver = robot->driver;
}

DerekDrive::~DerekDrive()
{
    delete encoder;
    delete shifter;
}
void DerekDrive::autoDrive(float dist) 
{
    if (!encoderState)
    {
        encoder->Start();
        encoderState = true;
    }
    TankDrive(0.7,0.7);
    if (encoder->GetDistance() >= dist) {
        encoder->Stop();
        encoderState = false;
        return;
    }
    
    
}
void DerekDrive::autoRotate()
{
    //TODO
}
void DerekDrive::doTeleOp()
{
    //do controls
    //TODO
    if(!(driver -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS)) || !(driver -> IsAxisZero(DRIVER_RIGHT_DRIVE_AXIS)))
    {
        TankDrive((driver -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS)),(driver -> GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS)));
    }
    else
    {
        TankDrive(0.0f, 0.0f);
    }
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
    TankDrive(0.0f, 0.0f);
}
void DerekDrive::setSafety()
{
    //TODO
}

void DerekDrive::update(bool mode)
{
    //TODO
}

