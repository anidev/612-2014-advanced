#include "Sensors.h"
#include "ports.h"

#include "main.h"
#include "612.h"

#include <cmath>

Sensors::Sensors()
{
    pnumSwitch = new DigitalInput(1, 8);
    left = new Encoder(5,6);
    left->SetReverseDirection(true);
    left->SetDistancePerPulse(0.0695);
    right = new Encoder(1,2);
    right->SetDistancePerPulse(0.092);
    ultrasonic = new AnalogChannel(3);
    infared = new AnalogChannel(4);
    infared2 = new AnalogChannel(5);
    ultrasonic2 = new Ultrasonic(6,7); //FAKE NOTHING THERE
    accel = new ADXL345_I2C(1);
    
    filename = "Sensors.txt";
    fp = new FileProcessor(filename, rw);
    curInfo = new char[256];
    left->Start();
    right->Start();
}
void Sensors::runSensors(int sense)
{
    static int count = 0;
    static double prevVal = -99.9;
    static int previousSense = -1;
    if (sense == 0)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!PnumSwitch (Digital Input)!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if ((double)pnumSwitch -> Get() != prevVal)
        {
            snprintf(curInfo, 100, "PnumSwitch: %f\n",(double)pnumSwitch -> Get());
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
        prevVal = (double)pnumSwitch -> Get();
    }
    else if(sense == 1)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!Left Encoder!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if ((double)left->Get() != prevVal)
        {
            snprintf(curInfo, 100, "Left Encoder: %f\n", (double)left->Get());
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
        prevVal = (double)left->Get();
    }
    else if (sense == 2)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!Right Encoder!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if ((double)right->Get() != prevVal)
        {
            snprintf(curInfo, 100, "Right Encoder: %f\n", (double)right->Get());
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
        prevVal = (double)right->Get();
    }
    else if (sense == 3)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!UltraSonic!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if (count % 50 == 0)
        {
            if ((double)ultrasonic->GetVoltage() != prevVal)
            {
                snprintf(curInfo, 100, "UltraSonic Voltage: %f\nUltraSonic Distance: %f\n\n", (double)ultrasonic->GetVoltage(), (double)ultrasonic->GetVoltage()/(0.0098));
                std::printf("%s", curInfo);
                fp->write(curInfo);
            }
        }
        prevVal = (double)ultrasonic->GetValue();
    }
    else if (sense == 4)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!UltraSonic2!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if (count % 50 == 0)
        {
            if ((double)ultrasonic2->GetRangeInches() != prevVal)
            {
                snprintf(curInfo, 100, "UltraSonic Voltage: %f\n", (double)ultrasonic2->GetRangeInches());
                std::printf("%s", curInfo);
                fp->write(curInfo);
            }
        }
        prevVal = (double)ultrasonic2->GetRangeInches();
    }
    else if (sense == 5)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!Infared!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if (count % 50 == 0)
        {
            double distance = (double)(infared->GetVoltage()*18.777777777777777); // about 1 cm off
            if ((double)infared->GetVoltage() != prevVal)
            {
                snprintf(curInfo, 100, "Infared Voltage: %f\nInfared Value: %f\nInfared Distance (cm): %f\n\n", (double)infared->GetVoltage(), (double)infared->GetValue(), distance);
                std::printf("%s", curInfo);
                fp->write(curInfo);
            }
        }
        prevVal = (double)infared->GetValue();
    }
    else if (sense == 6)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!Infared2!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.9;
        }
        if (count % 50 == 0)
        {
            double distance = (double)(infared->GetVoltage()*18.777777777777777); // about 1 cm off
            if ((double)infared->GetVoltage() != prevVal)
            {
                snprintf(curInfo, 100, "Infared Voltage: %f\nInfared Value: %f\nInfared Distance (cm): %f\n\n", (double)infared->GetVoltage(), (double)infared->GetValue(), distance);
                std::printf("%s", curInfo);
                fp->write(curInfo);
            }
        }
        prevVal = (double)infared->GetValue();
    }
    else if (sense == 7)
    {
        if (previousSense != sense)
        {
            snprintf(curInfo, 100, "!!Accelorometer!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.99;
        }
        if (count % 25 == 0)
        {
            /*
            double xAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
            double yAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
            double zAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
            
            //double roll = atan(-yAxis/zAxis)*(180/3.141592654);
            double pitch = atan(xAxis/(sqrt((yAxis*yAxis) + (zAxis*zAxis))))*(180/3.141592654);
            */
            // commented out because of implementation of getPitch()
            std::printf("Pitch: %f\n", getPitch());
            //std::printf("Roll: %f\n\n", roll);
            /*
            if(zAxis != prevVal)
            {
                snprintf(curInfo, 100, "Accelerometer X: %f\n",xAxis);
                std::printf("%s", curInfo);
                fp->write(curInfo);
                
                snprintf(curInfo, 100, "Accelerometer Y: %f\n",yAxis);
                std::printf("%s", curInfo);
                fp->write(curInfo);
                
                snprintf(curInfo, 100, "Accelerometer Z: %f\n\n",zAxis);
                std::printf("%s", curInfo);
                fp->write(curInfo);
            }
            */
        }
    }
    else if (sense == 8)
    {
        if (previousSense != sense)
            std::printf("!!Encoders!!\n");
        static int rightPrev = 0;
        static int leftPrev = 0;
        static int count = 0;
        int leftVal = left->Get();
        int rightVal = right->Get();
        if (count % 15 == 0)
        {
            if (true/*leftVal != leftPrev || rightVal != rightPrev*/)
            {
                std::printf("Left encoder: %i\nRight encoder: %i\n", leftVal, rightVal);
                std::printf("Left Distance: %f\nRight Distance: %f\n",left->GetDistance(), right->GetDistance());
                std::printf("Average Distance: %f\n\n", (right->GetDistance() + left->GetDistance())/2.0);
            }
        }
        drive();
        count++;
        rightPrev = rightVal;
        leftPrev = leftVal;
        if (robot->driverJoy->GetRawButton(8))
        {
            left->Reset();
            right->Reset();
            std::printf("RESET!\n");
        }
    }
    else if (sense >= 9)
    {
        snprintf(curInfo, 100, "MAX\n");
        std::printf("%s", curInfo);
        fp->write(curInfo);
        robot->selection = 80;
    }
    previousSense = sense;
    count++;
    //prevVal = sense;
}
void Sensors::drive()
{
    float l = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    float r = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
    
    robot->motors->FL -> Set(-l);
    robot->motors->RL -> Set(-l);
    
    robot->motors->FR -> Set(r);
    robot->motors->RR -> Set(r);
}
double Sensors::getPitch()
{
    double xAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
    double yAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
    double zAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
    
    //double roll = atan(-yAxis/zAxis)*(180/3.141592654);
    double pitch = atan(xAxis/(sqrt((yAxis*yAxis) + (zAxis*zAxis))))*(180/3.141592654);
    return pitch;
}
