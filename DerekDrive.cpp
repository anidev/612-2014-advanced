#include "DerekDrive.h"
#include "main.h"
#include "612.h"
#include "UpdateRegistry.h"

DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2,
                       uint32_t modEncRA, uint32_t chanEncRA,
                       uint32_t modEncRB, uint32_t chanEncRB,
                       uint32_t modEncLA, uint32_t chanEncLA,
                       uint32_t modEncLB, uint32_t chanEncLB,
                       uint8_t modFL,uint32_t chanFL,
                       uint8_t modRL,uint32_t chanRL,
                       uint8_t modFR,uint32_t chanFR,
                       uint8_t modRR,uint32_t chanRR)
                    :RobotDrive(new Talon(modFL,chanFL),
                                new Talon(modRL,chanRL),
                                new Talon(modFR,chanFR),
                                new Talon(modRR,chanRR))
{
    shifter = new Shift(shift1,shift2);
    isAsync = false;
    //robot_class* robot = (robot_class*)o;
    drivePower = 1.0;
    //shift LOW (or high, but we need to have a default as seen from last year)
    driver = robot->driver;
    //Encoders
    encoderState = false;
    encoderL = new Encoder(modEncRA, chanEncRA, modEncRB, chanEncRB);
    encoderR = new Encoder(modEncLA, chanEncLA, modEncLB, chanEncLB);
    
    encoderL->SetDistancePerPulse(0.015);
    encoderR->SetDistancePerPulse(0.015);
    
    robot->updateRegistry.add(this, &update);

}

DerekDrive::~DerekDrive()
{
    delete encoderR;
    delete encoderL;
    delete shifter;
}
void DerekDrive::autoDrive(float dist) 
{
    if (!encoderState)
    {
        startEncoders();
    }
    TankDrive(0.7,0.7);
    if (((encoderDistance(RIGHT) + encoderDistance(LEFT))/2) >= dist) 
    {
        stopEncoders();
        return;
    }
}
void DerekDrive::autoRotate()
{
    //TODO
}
void DerekDrive::doTeleOp()
{
    if(!(driver -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS)) || !(driver -> IsAxisZero(DRIVER_RIGHT_DRIVE_AXIS)))
    {
        float left = driver -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
        float right = driver -> GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
        TankDrive(left,right);
        static int output = 0;
        if (output%20 == 0) {
            printf("left: %f, right: %f", left, right);
        }
        output++;
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
    TankDrive(0.0f, 0.0f);
}
void DerekDrive::setSafety()
{
    //TODO
}

void DerekDrive::update(void* o)
{
    DerekDrive* thisObj = (DerekDrive*)o;
    thisObj->doTeleOp();
}

float DerekDrive::encoderDistance(side s)
{
    if (s == RIGHT)
        return (encoderR->GetRaw());
    else 
        return (encoderL->GetRaw());
}
void DerekDrive::startEncoders()
{
    encoderR->Start();
    encoderL->Start();
    encoderState = true;
}
void DerekDrive::stopEncoders()
{
    encoderR->Stop();
    encoderL->Stop();
    encoderState = false;
}
