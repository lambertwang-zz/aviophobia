#pragma once
/*
 * Keyboard input
 *
 * Enum copied from Professor Claypool's code
 */

#ifndef __INPUT_H__
#define __INPUT_H__

// SDL
#include <SDL.h>

namespace av {

namespace Input {

enum MouseButton {
    UNDEFINED_MOUSE_BUTTON = -1,
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MouseButtonEnumEnd,
};

enum Axis {
    UNDEFINED_AXIS = -1,
    AXIS_X,
    AXIS_Y,
    AXIS_Z,
    AXIS_R,
    AXIS_U,
    AXIS_V,
    AXIS_PovX,
    AXIS_PovY,
    AxisEnumEnd,
};

} // end of namespace

} // end of namespace
#endif // __INPUT_H__
