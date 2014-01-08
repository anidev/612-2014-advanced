#include "SmoothJoystick.h"


Trigger SmoothJoystick::GetTriggerState() {
    float value=GetRawAxis(TRIGGER_AXIS);
    if(value<TRIGGER_TOLERANCE-1) {
        return TRIG_R;
    } else if(value>1-TRIGGER_TOLERANCE) {
        return TRIG_L;
    }
    return TRIG_NONE;
}
