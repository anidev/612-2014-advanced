#include "Motors.h"
#include "main.h"
#include "612.h"
#include <Relay.h>
Motors::Motors()
{
    FR = new Talon(TALON_FL_MODULE, TALON_FL_CHANNEL); //drivetrain
    FL = new Talon(TALON_RL_MODULE, TALON_RL_CHANNEL);
    RR = new Talon(TALON_FR_MODULE, TALON_FR_CHANNEL);
    RL = new Talon(TALON_RR_MODULE, TALON_RR_CHANNEL);

    grabber = new Talon(GRAB_MOD, GRAB_CHAN);
    
    tilt = new CANJaguar(TILT_DEV);
    
    compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    /*
    motors.push_back({"FRTalon",TALON,TALON_FR_MODULE,TALON_FR_CHANNEL,FR});
    motor_info FLinfo   = {"FLTalon",TALON,TALON_FL_MODULE,TALON_FL_CHANNEL,FL};
    motor_info RRinfo   = {"RRTalon",TALON,TALON_RR_MODULE,TALON_RR_CHANNEL,RR};
    motor_info RLinfo   = {"RLTalon",TALON,TALON_RL_MODULE,TALON_RL_CHANNEL,RL};
    motor_info compinfo = {"Compressor",RELAY,PNUM_RELAY_MODULE,PNUM_RELAY_CHANNEL,compressor};
    */
    //joy = robot->driverJoy;
}

Motors::~Motors()
{
}

void Motors::runMotor(int motor)
{
    static bool print = false;
    static int previousMotor = -1;
    static float previousPower = 0.0;
    
    power = robot->driverJoy -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    
    if ((previousMotor != motor) || previousPower != power) 
    {
        print = true;
        previousMotor = motor;
        previousPower = power;
    }
    else
    {
        print = false;
    }
    if (motor >= 0 && motor <10)
    {
        drive(); //implementation of RobotDrive
        if (print)
            std::printf("Drivetrain: %f\n", power);
    }
    else if (motor >= 10 && motor <20)
    {
        FR -> Set(power);
        if (print)
            std::printf("1: Talon 7 %f\n", power);
    }
    else if (motor >= 20 && motor < 30)
    {
        FL -> Set(power);
        if (print)
            std::printf("2: Talon 1 %f\n", power);
    }
    else if (motor >= 30 && motor < 40)
    {
        RR -> Set(power);
        if (print)
            std::printf("3: Talon 6 %f\n", power);
    }
    else if (motor >= 40 && motor < 50)
    {
        RL -> Set(power);
        if (print)
            std::printf("4: Talon 2 %f\n", power);
    }
    else if (motor >= 50 && motor < 60) //grabber
    {
        grabber -> Set(power);
        if (print)
            std::printf("5: Grabber Talon 3 %f\n", power);
    }
    else if (motor >= 70 && motor < 80) //tilt JAG
    {
        tilt -> Set(power);
        if (print)
            std::printf("6: Jag Tilt: %f\n", power);
    }
    else if (motor >= 60 && motor < 70) //Compressor NEVER SET TO REVERSE
    {
        static Relay::Value compressorDirection = Relay::kReverse;
        if ((robot->driverJoy -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS) == false) && (robot->sense->pnumSwitch->Get() == 0))
        {
            compressor->Set(Relay::kForward);
            if (compressorDirection != Relay::kForward)
            {
                std::printf("Compressor: kForward\n");
                compressorDirection = Relay::kForward;
            }
        }
        else 
        {
            compressor->Set(Relay::kOff);
            if (compressorDirection != Relay::kOff)
            {
                std::printf("Compressor: kOff\n");
                compressorDirection = Relay::kOff;
            }
        }
    }
    else if (motor >= 80)
    {
        std::printf("MAX\n");
        robot->selection = 79;
    }
}
void Motors::drive()
{
    left = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
    
    FL -> Set(left);
    RL -> Set(left);
    
    FR -> Set(right);
    RR -> Set(right);
}
void Motors::disable()
{
    FL->Set(0.0);
    FR->Set(0.0);
    RR->Set(0.0);
    RL->Set(0.0);
    
    grabber->Set(0.0);
    
    tilt->Set(0.0);
    
    compressor->Set(Relay::kOff);
}
