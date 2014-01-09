#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
//#include <Relay.h>
//#include <DigitalInput.h>

class robot_class : public IterativeRobot
{
public:
    robot_class();

    void RobotInit();

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
private:
    //Relay compressor;
    //DigitalInput pnumSwitch;
};

#endif // MAIN_H
