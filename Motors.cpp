#include "Motors.h"
#include "main.h"
#include "612.h"
#include <Relay.h>

Motors::Motors()
{
    FR = new Talon(1,7); //drivetrain
    FL = new Talon(1,1);
    RR = new Talon(1,6);
    RL = new Talon(1,2);

    drivetrain [0] = FR;
    drivetrain [1] = FL;
    drivetrain [2] = RR;
    drivetrain [3] = RL;
    
    
    grabber = new Talon(1,3);
    
    tilt = new CANJaguar(1);
    wormDrive = new Talon(1,1); //TODO NOT THE REAL PORTS
    
    compressor = new Relay(1,8);
    filename = "Motors.txt";
    fp = new FileProcessor(filename, rw);
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
    
    if (motor == 0 && (power > 0.1 || power < -0.1))
    {
        if (print)
        {
            snprintf(curInfo, 100, "Drivetrain\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
        drive(print); //implementation of RobotDrive
    }
    else if (motor >= 1 && motor <=4)
        setTalon(motor,print);
    else if (motor == 5)
        setTalon(grabber,print,motor);
    else if (motor == 6) //Compressor NEVER SET TO REVERSE
        runCompressor(compressor, power, print);
    else if (motor == 7) //tilt JAG
        runJag(tilt, power, print);
    else if (motor == 8)
        setTalon(wormDrive,print,motor);
    else if (motor >= 9)
    {
        snprintf(curInfo, 100, "MAX\n");
        std::printf("%s", curInfo);
        fp->write(curInfo);
        robot->selection = 80;
    }
    previousMotor = motor;
}
void Motors::drive(bool print)
{
    left = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
    
    FL -> Set(left);
    RL -> Set(left);
    
    FR -> Set(right);
    RR -> Set(right);
    if (print)
    {
        snprintf(curInfo, 100, "Drivetrain: %f\n", power);
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
}
void Motors::drive2(bool print)
{
    //TODO I want to test this first, not sure if it will work
    left = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);

    for (int i=0;i<4;i++)
        drivetrain[i] ->Set(power);

    if (print)
    {
        snprintf(curInfo, 100, "Drivetrain Power: %f\n", power);
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
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
    
    robot->speed = 0.0;
}
void Motors::setTalon(Talon* t, bool print, int motor) //bool print, int motor, Talon* t = null
{
    if (print == true && motor == 5)
    {
        snprintf(curInfo, 100, "%d: Talon (Roller) %u : %f\n",motor, 0, power);
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
    else if (print == true && motor == 8)
    {
        snprintf(curInfo, 100, "%d: Talon (Worm Drive) %u : %f\n",motor, 0, power);
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
    if (power > 0.1 || power < -0.1)
    {
        t -> Set(power);
    }
    else
    {
        t -> Set(0.0);
    }
    if (motor == 8)
        controlPiston();
}
void Motors::setTalon(int motor, bool print)
{
    if (print)
    {
        snprintf(curInfo, 100, "%d: Talon %u : %f\n",motor, 0, power);
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
    if (power > 0.1 || power < -0.1)
    {
        drivetrain[motor-1] -> Set(power);   
    }
}
void Motors::runJag(CANJaguar* jag, float power, bool print)
{
    if (power > 0.15 || power < -0.15)
    {
        if (robot->driverJoy->GetRawButton(BUTTON_START))
        {
            if (power < 0)
                power = 0.6;
            else
                power = -0.6;
            jag -> Set(power);
        }
        else
        {
            jag -> Set(-power);
        }
        if (print)
        {
            snprintf(curInfo, 100, "7: Jag Tilt: %f\n", power);
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
    }
    else 
    {
        jag -> Set(0.0);
        if (print)
        {
            snprintf(curInfo, 100, "7: Jag Tilt: off\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
    }
}

void Motors::runCompressor(Relay* relay, float power, bool print)
{
    if (print)
    {
        snprintf(curInfo, 100, "Compressor\n");
        std::printf("%s", curInfo);
        fp->write(curInfo);
    }
    static bool warned = false;
    static Relay::Value compressorDirection = Relay::kReverse;
    if (robot->driverJoy->GetRawButton(BUTTON_START) && ((power > JOYSTICK_ZERO_TOLERANCE) || (power < JOYSTICK_ZERO_TOLERANCE*-1)))
    {
        relay->Set(Relay::kForward);
        if (compressorDirection != Relay::kForward)
        {
            if (!warned)
            {
                std::printf("RELAY OVERRIDE: WILL NOT TURN OFF AUTOMATICALLY\n");
                fp->write(curInfo);
                warned = true;
            }
            std::printf("Compressor: kForward\n");
            fp->write(curInfo);
            compressorDirection = Relay::kForward;
        }
    }
    else if ((robot->driverJoy -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS) == false) && (robot->sense->pnumSwitch->Get() == 0))
    {
        relay->Set(Relay::kForward);
        if (compressorDirection != Relay::kForward)
            compressorDirection = Relay::kForward;
        {
            std::printf("Compressor: kForward\n");
            fp->write(curInfo);
        }
    }
    else 
    {
        warned = false;
        relay->Set(Relay::kOff);
        if (compressorDirection != Relay::kOff)
        {
            std::printf("Compressor: kOff\n");
            fp->write(curInfo);
            compressorDirection = Relay::kOff;
        }
    }
}
void Motors::controlPiston()
{
    if (robot->driverJoy->GetRawAxis(5) > 0.15)
        robot->pneumatics->piston->Set(DoubleSolenoid::kForward);
    else if (robot->driverJoy->GetRawAxis(5) < -0.15)
        robot->pneumatics->piston->Set(DoubleSolenoid::kReverse);
    else
        robot->pneumatics->piston->Set(DoubleSolenoid::kOff);        
}

