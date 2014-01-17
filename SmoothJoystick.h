#ifndef SMOOTH_JOYSTICK_H
#define SMOOTH_JOYSTICK_H

#include <Joystick.h>
#include "Controls.h"
#include <vector>
#include <bitset>


class SmoothJoystick : public Joystick 
{
public:
    /*
    static const float JOYSTICK_ZERO_TOLERANCE = 0.1;
    static const float TRIGGER_TOLERANCE = 0.25;
    */
    SmoothJoystick(UINT32);
    ~SmoothJoystick();
    bool GetRawButton(UINT32 btn);
    bool IsAxisZero(unsigned int);
    Trigger GetTriggerState();
    typedef void* obj;
    typedef void(*helpFunc)(obj);
    void pushBtn(UINT32,obj,helpFunc);
    void updateSJ();
private:
    const static unsigned int NUMBUTTONS = 12;
    const static unsigned int WAIT_TIME = 3;
    std::bitset<WAIT_TIME> buttons[NUMBUTTONS];
    void callFunct(unsigned int);
    std::vector<UINT32> btnNumbers;
    std::vector<obj> objects;
    std::vector<helpFunc> helpers;
    std::vector<bool> prevState;
};

#endif 
