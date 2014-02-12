#include "Sensors.h"
#include "ports.h"

#include "main.h"
#include "612.h"

Sensors::Sensors()
{
    pnumSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
    left = new Encoder(LEFT_ENCODER_A_MOD,LEFT_ENCODER_A_CHAN,LEFT_ENCODER_B_MOD,LEFT_ENCODER_B_CHAN);
    right = new Encoder(RIGHT_ENCODER_A_MOD,RIGHT_ENCODER_A_CHAN,RIGHT_ENCODER_B_MOD,RIGHT_ENCODER_B_CHAN);
    ultrasonic = new AnalogChannel(ULTRASONIC_MODULE, ULTRASONIC_CHANNEL);
    infared = new AnalogChannel(IR_MODULE,IR_CHANNEL);
    ultrasonic2 = new Ultrasonic(2,1);
    accel = new ADXL345_I2C(1);
    
    filename = "Sensors.txt";
    fp = new FileProcessor(filename, rw);
    
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
            snprintf(curInfo, 100, "!!Accelorometer!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            prevVal = -99.99;
        }
        if (count % 25 == 0)
        {
            double xAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
            double yAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
            double zAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
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
        }
    }
    else if (sense >= 7)
    {
        snprintf(curInfo, 100, "MAX\n");
        std::printf("%s", curInfo);
        fp->write(curInfo);
        robot->selection = 60;
    }
    previousSense = sense;
    count++;
    //prevVal = sense;
}
