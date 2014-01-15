#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Talon.h>
#include "main.h"
#include "Shift.h"

class DerekDrive : public RobotDrive 
{
    public:
        DerekDrive(uint32_t shift1, uint32_t shift2, uint32_t shift3, uint32_t shift4, uint32_t pnumSwitch, uint32_t compressor, uint8_t modFL,uint32_t chanFL,uint8_t modRL,uint32_t chanRL,uint8_t modFR,uint32_t chanFR,uint8_t modRR,uint32_t chanRR,void*);
        ~DerekDrive();
        void autoDrive(float,float);
        void autoRotate();
        void doTeleOp();
        void stop();
        void setSafety();
        void update(bool);
        void shiftGear();
    private:
        /*
        SpeedController frontLeft;
        SpeedController frontRight;
        SpeedController rearLeft;
        SpeedController rearRight;
        */
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
        Shift* shifter;
};
#endif
