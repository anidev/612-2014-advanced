#include "Motors.h"

Motors::Motors()
{
    FR = new Talon(TALON_FL_MODULE, TALON_FL_CHANNEL); //drivetrain
    FL = new Talon(TALON_RL_MODULE, TALON_RL_CHANNEL);
    RR = new Talon(TALON_FR_MODULE, TALON_FR_CHANNEL);
    RL = new Talon(TALON_RR_MODULE, TALON_RR_CHANNEL);
    
    grabber = new Talon(GRAB_MOD, GRAB_CHAN);
    
    tilt = new CANJaguar(TILT_DEV);
    
    compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    
    SmoothJoystick* joy = robot->driverJoy;
    
    pnumSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
}

void Motors::runMotor(int motor)
{
    power = joy -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    if (motor == 0)
        drive(); //implementation of RobotDrive
    else if (motor == 1)
        FR -> Set(power);
    else if (motor == 2)
        FL -> Set(power);
    else if (motor == 3)
        RR -> Set(power);
    else if (motor == 4)
        RL -> Set(power);
    
    else if (motor == 5) //grabber
        grabber -> Set(power);
    else if (motor == 6) //tilt JAG
        tilt -> Set(power);
    
    else if (motor == 7) //Compressor NEVER SET TO REVERSE
        if ((joy -> isAxisZero(DRIVER_LEFT_DRIVE_AXIS) == false) && (robot->sense->pnumSwitch->Get() == 0))
            compressor->Set(Relay::kForward);
}
void Motors::drive()
{
    left = joy -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = joy -> GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
    
    FL -> Set(left);
    RL -> Set(left);
    
    FR -> Set(right);
    RR -> Set(right);
}
    