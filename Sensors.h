#ifndef SENSORS_H
#define SENSORS_H

#include <DigitalInput.h>
#include <Encoder.h>
#include <AnalogChannel.h>
#include <Ultrasonic.h>
#include <ADXL345_I2C.h>

#include "612.h"
#include "FileProcessor.h"

class Sensors
{
public:
    Sensors::Sensors();
    void runSensors(int sense);
    
    DigitalInput* pnumSwitch; //DIO 8
    
    float inputs[3];
    
    Ultrasonic* ultrasonic2;
    
    Encoder* left; //4,5
    Encoder* right; //6,7
    AnalogChannel* ultrasonic;
    AnalogChannel* infared;

    ADXL345_I2C* accel;
    
    char* curInfo;
    char* filename;
    FileProcessor* fp;
    
private:
    //sensors
};

#endif
