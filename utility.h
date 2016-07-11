#pragma once
/*
 * Dragonfly utility functions
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

// dragonfly headers
#include "WorldManager.h"

namespace av {

// Returns a *char of the current time in 
// the form of a human readable string
char *getTimeString();

// Gets the current time in microseconds
long int getCurrentTime();

// Sleeps for some number of nanoseconds
// Nanosleep cannot sleep more than 1 second at a time
// @param nanoseconds Amount of time in nanoseconds to sleep
void nanoSleep(long nanoseconds);

// Converts an int to a string
std::string intToString(int i);

} // End of namespace

#endif // __UTILITY_H__
