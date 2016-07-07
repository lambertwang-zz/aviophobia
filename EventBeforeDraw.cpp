/*
 * Event Beforedraw class
 */

// Dragonfly headers
#include "EventBeforeDraw.h"

av::EventBeforeDraw::EventBeforeDraw() {
    // "av::beforedraw"
    this->setType(av::BEFOREDRAW_EVENT);
}
