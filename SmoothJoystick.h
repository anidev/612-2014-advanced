#ifndef SMOOTH_JOYSTICK_H
#define SMOOTH_JOYSTICK_H

#include <Joystick.h>
#include "Controls.h"


class SmoothJoystick : public Joystick {
public:
    static const float JOYSTICK_ZERO_TOLERANCE = 0.1;
    static const float TRIGGER_TOLERANCE = 0.25;
    SmoothJoystick(UINT32);
    ~SmoothJoystick();
    bool GetRawButton(UINT32 btn);
    bool IsAxisZero(unsigned int);
    Trigger GetTriggerState();
private:
    
};

#endif 
