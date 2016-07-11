/*
 * Utilty functions
 */

// c++ standard libraries
#include <sstream>
#include <stdio.h>
#include <time.h>
// Platform conditionals taken from a stackOverflow question
// http://stackoverflow.com/questions/3627127/writing-cross-platform-c-code-windows-linux-and-mac-osx
#ifdef TARGET_OS_MAC
    #include <sys/time.h>
#elif defined __linux__
//    #include <time.h>
#elif defined _WIN32 || defined _WIN64
    #include <Windows.h>
#else
#error "unknown platform"
#endif

// Dragonfly headers
#include "utility.h"

// Returns a human-readable timestring
char *av::getTimeString() {
    static char timebuf[26];
#if defined _WIN32 || defined _WIN64
    struct tm newtime;
    time_t time;
    errno_t err;

    // Get time as 64-bit integer.
    _time64(&time);

    // Convert to local time.
    err = _localtime64_s(&newtime, &time);
    if (err) {
        printf("Invalid argument to _localtime64_s.");
        exit(1);
    }

    // Convert to an ASCII representation. 
    err = asctime_s(timebuf, 26, &newtime);
    if (err) {
        printf("Invalid argument to asctime_s.");
        exit(1);
    }
    return timebuf;
#else
    // System calls for current time
    time_t now;
    time(&now);

    struct tm *p_time = localtime(&now);
    localtime_s()

        // String formatting
        sprintf(timebuf, "%02d:%02d:%02d", p_time->tm_hour, p_time->tm_min, p_time->tm_sec);

    return timebuf;
#endif
}

long int av::getCurrentTime() {
    // Calculates time in milliseconds from seconds and nanoseconds
    #ifdef TARGET_OS_MAC
        struct timeval current_tv;
        gettimeofday(&current_tv, NULL);

        return current_tv.tv_sec*1000 + current_tv.tv_nsec/1000000;
    #elif defined __linux__
        struct timespec current_time;
        clock_gettime(CLOCK_REALTIME, &current_time);
        
        return current_time.tv_sec*1000 + current_time.tv_nsec/1000000;
    #elif defined _WIN32 || defined _WIN64
        SYSTEMTIME current_st;
        GetSystemTime(&current_st);
    
        // Calculates time in microseconds from minutes, seconds, and milliseconds
        return (current_st.wMinute*60*1000)
                + (current_st.wSecond*1000)
                + (current_st.wMilliseconds);
    #else
    #error "unknown platform"
    #endif
}

void av::nanoSleep(long nanoseconds) {
    #if defined TARGET_OS_MAC || defined __linux__
        // Construct a timespec with the specified nanoseconds
        struct timespec sleep_time;
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = nanoseconds*1000;
        nanosleep(&sleep_time, NULL);
    #elif defined _WIN32 || defined _WIN64
        if (nanoseconds > 0) {
            Sleep(nanoseconds/1000000);
        }
    #else
    #error "unknown platform"
    #endif
}

std::string av::intToString(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}
