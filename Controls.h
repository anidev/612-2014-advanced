#ifndef CONTROLS_H
#define CONTROLS_H

typedef unsigned int Button;
typedef unsigned int Axis;

enum Trigger 
{
    TRIG_NONE = 0,
    TRIG_L = -1,
    TRIG_R = 1
};

static const float DRIVE_POWER = 1.0;

static const float JOYSTICK_ZERO_TOLERANCE = 0.1;
static const float TRIGGER_TOLERANCE = 0.25;
static const Axis TRIGGER_AXIS = 3; //may need to rename this later
//TODO Rumble

static const unsigned int DRIVER_JOY = 1;
static const unsigned int GUNNER_JOY = 2;

static const Button SHIFT_LOW  = 5; //L1
static const Button SHIFT_HIGH = 6; //R1

static const Button BUTTON_CLAMP_DOWN = 1; //A
static const Button BUTTON_CLAMP_UP   = 2; //B

static const Button BUTTON_TILT_DOWN  = 3; //X
static const Button BUTTON_TILT_UP    = 4; //Y


//Copied post from XBOX thread
/*
Buttons
01: A (green/bottom)
02: B (red/right)
03: X (blue/left)
04: Y (yellow/top)
05: Left Bumper (L1)
06: Right Bumper (R1)
07: Back (left)
08: Start (right)
09: Left Joystick Click
10: Right Joystick Click

Axes
01: Left Joystick X: -left, +right
02: Left Joystick Y: -up, +down
03: Triggers (L2/R2): -right, +left, 0 at rest, 0 if both pressed
04: Right Joystick X: -left, +right
05: Right Joystick Y: -up, +down
06: DPad X: -left, +right
*/
//no D-Pad Y axis

static const Axis DRIVER_LEFT_DRIVE_AXIS = 2;//L Stick
static const Axis DRIVER_RIGHT_DRIVE_AXIS = 5;//R Stick


#endif
