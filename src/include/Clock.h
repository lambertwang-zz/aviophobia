#pragma once
/*
 * Clock class header
 *
 * Used to calculate time accurate to the microsecond
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace av {

    class Clock {
    private:
        // Previous time delta() called in microseconds
        long int previous_time;

    public:
        // Sets previous time to current time
        Clock();

        // Returns time in microseconds since delta() was last called
        // Returns -1 if error
        long int delta(void);

        // Returns time in microseconds since delta() was last called
        // Does not change previous_time
        // Returns -1 if error
        long int split(void) const;
    };
} // End of namespace

#endif // __CLOCK_H__
