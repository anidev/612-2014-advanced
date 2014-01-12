#include "SmoothJoystick.h"

SmoothJoystick::SmoothJoystick(UINT32 a) : Joystick(a) {
    
}

SmoothJoystick::~SmoothJoystick() {
    
}

void SmoothJoystick::pushBtn(UINT32 btn, obj o, helpFunc h) {
    btnNumbers.push_back(btn);
    objects.push_back(o);
    helpers.push_back(h);
    prevState.push_back(false);
}

void SmoothJoystick::updateSJ() {
    for (unsigned int f = 0; f < NUMBUTTONS; f++){
        for (unsigned int s = 1; s < WAIT_TIME; s++){
            buttons[f][s - 1] = buttons [f][s];
        }
        buttons[f][WAIT_TIME - 1] = Joystick::GetRawButton(f+1);
    } 
    for (unsigned int x = 0; x < btnNumbers.size(); x++) {
        if(GetRawButton(btnNumbers.at(x)) && !prevState.at(x)) {
            callFunct(x);
            prevState.at(x) = true;
        } else if (!GetRawButton(btnNumbers.at(x))) {
            prevState.at(x) = false;
        }
    }
}

Trigger SmoothJoystick::GetTriggerState() {
    float value=GetRawAxis(TRIGGER_AXIS);
    if(value<TRIGGER_TOLERANCE-1) {
        return TRIG_R;
    } else if(value>1-TRIGGER_TOLERANCE) {
        return TRIG_L;
    }
    return TRIG_NONE;
}

void SmoothJoystick::callFunct(unsigned int x) {
    (helpers.at(x))(objects.at(x));
}

bool SmoothJoystick::GetRawButton(UINT32 btn) {
    for (unsigned int i = 0; i < WAIT_TIME; i++){
       if (!buttons[btn - 1][i]){
           return false;
       }
   }
   return true;
}
