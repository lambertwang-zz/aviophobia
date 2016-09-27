#pragma once
/*
 * Log manager class header
 *
 * Logs messages to aviophobia.log
 */

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// c++ standard libraries
#include <stdarg.h>
#include <stdio.h>

// SDL headers
#include <SDL_thread.h>

// aviophobia headers
#include "Manager.h"

// Used to determine logging frequency
#define LOG_NONE 0x00
#define LOG_DEFAULT 0x01
#define LOG_GAME_TICK 0x02
#define LOG_FRAME 0x04
#define LOG_STARTUP 0x08 // When managers are started, shutdown, or have settings changed
#define LOG_EVENT 0x10
#define LOG_RESOURCE 0x20
#define LOG_OBJECT 0x40
#define LOG_ALL 0xff // Errors are included in LOG_ALL by default

namespace av {

const std::string LOGFILE_NAME = "aviophobia.log";

    class LogManager : public Manager {
    private:
        // Singleton
        LogManager();
        // Disallow copy
        LogManager(LogManager const&);
        // Disallow assignment
        void operator=(LogManager const&);

        // True if manager flushes to disk after each write
        bool do_flush;

        // The logging level of the manager
        unsigned char log_level;

        // Pointer to logfile struct
        FILE *p_f; 

    public:
        // If logfile is open, close it
        ~LogManager();

        // Get the instance of the singleton
        static LogManager &getInstance();

        // Invokes startUp(INT_MAX)
        int startUp();
        // Start the LogManager and open file
        // Returns 0 if successful negative otherwise
        int startUp(unsigned char log_level);

        // Shut down LogManager and close file
        void shutDown();

        // Set flush of logfile after each write
        void setFlush(bool do_flush=true);

        // Sets the logging level of this manager
        void setLogLevel(unsigned char log_level);
        // Returns the logging level of this manager
        unsigned char getLogLevel() const;

        // Invokes vfWriteLog with MAXINT as log_level
        int writeLog(const char *fmt, ...);
        // Write to logfile. Supports printf() formatting of strings
        // Returns number of bytes written. -1 if error
        int writeLog(unsigned char log_level, const char *fmt, ...);

        static SDL_mutex *m_log_manager;
    };
} // End of namespace

#endif // __LOG_MANAGER_H__


