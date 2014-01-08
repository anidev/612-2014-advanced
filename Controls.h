#ifndef CONTROLS_H
#define CONTROLS_H

typedef unsigned int Button;
typedef unsigned int Axis;

enum Trigger {
    TRIG_NONE = 0,
    TRIG_L = -1,
    TRIG_R = 1
};

static const Axis TRIGGER_AXIS = 3; //may need to rename this later

#endif
