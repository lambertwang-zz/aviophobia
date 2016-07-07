#pragma once
/*
 * Event Before Draw class header
 *
 * This event is passed to objects on every frame before the draw call
 */

#ifndef __EVENT_BEFOREDRAW_H__
#define __EVENT_BEFOREDRAW_H__

// c++ standard libraries
#include <string>

// Dragonfly headers
#include "Event.h"

namespace av {

const std::string BEFOREDRAW_EVENT = "av::beforedraw";

    class EventBeforeDraw : public Event {
    private:
    public:
        // base constructor
        EventBeforeDraw();
    };
} // End of namespace

#endif // __EVENT_BEFOREDRAW_H__
