#include "DerekDrive.h"
#include "main.h"
#include "Shift.h"
#include "612.h"

DerekDrive::DerekDrive(uint32_t shift1, uint32_t shift2,
                       uint32_t modEncFRA, uint32_t chanEncFRA,
                       uint32_t modEncFRB, uint32_t chanEncFRB,
                       uint32_t modEncFLA, uint32_t chanEncFLA,
                       uint32_t modEncFLB, uint32_t chanEncFLB,
                       uint32_t modEncRRA, uint32_t chanEncRRA,
                       uint32_t modEncRRB, uint32_t chanEncRRB,
                       uint32_t modEncRLA, uint32_t chanEncRLA,
                       uint32_t modEncRLB, uint32_t chanEncRLB,
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
    encoderFR = new Encoder(modEncFRA, chanEncFRA, modEncFRB, chanEncFRB);
    encoderFL = new Encoder(modEncFLA, chanEncFLA, modEncFLB, chanEncFLB);
    encoderRL = new Encoder(modEncRRA, chanEncRRA, modEncRRB, chanEncRRB);
    encoderRR = new Encoder(modEncRLA, chanEncRLA, modEncRLB, chanEncRLB);
    encoderFR->SetDistancePerPulse(0.015);
    encoderFL->SetDistancePerPulse(0.015);
    encoderRR->SetDistancePerPulse(0.015);
    encoderRL->SetDistancePerPulse(0.015);
}

DerekDrive::~DerekDrive()
{
    delete encoderFR;
    delete encoderFL;
    delete encoderRR;
    delete encoderRL;
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

float DerekDrive::encoderDistance(side s)
{
    if (s == RIGHT)
        return (encoderFR->GetRaw() + encoderRR->GetRaw()/2);
    else 
        return (encoderFL->GetRaw() + encoderRL->GetRaw()/2);
}
void DerekDrive::startEncoders()
{
    encoderFR->Start();
    encoderFL->Start();
    encoderRR->Start();
    encoderRL->Start();
    encoderState = true;
}
void DerekDrive::stopEncoders()
{
    encoderFR->Stop();
    encoderFL->Stop();
    encoderRR->Stop();
    encoderRL->Stop();
    encoderState = false;
}
