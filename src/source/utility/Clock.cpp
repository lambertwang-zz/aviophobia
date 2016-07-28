/*
 * Clock class
 */

// Dragonfly headers
#include "Clock.h"
#include "utility.h"

av::Clock::Clock() {
    // Initialize time to current time
    this->previous_time = av::getCurrentTime();
}

long int av::Clock::split(void) const {
    // Calculate difference
    long int elapsed_time = av::getCurrentTime()-this->previous_time;
    // If elapsed time is zero or positive, return elapsed time
    return elapsed_time >= 0 ? elapsed_time : -1;
}

long int av::Clock::delta(void) {
    // Call split to get time difference
    long int elapsed_time = this->split();
    // Reset previous time
    this->previous_time = av::getCurrentTime();
    // If elapsed time is zero or positive, return elapsed time
    return elapsed_time;
}
