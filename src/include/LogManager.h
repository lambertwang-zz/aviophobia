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
        int log_level;

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
        int startUp(int log_level);

        // Shut down LogManager and close file
        void shutDown();

        // Set flush of logfile after each write
        void setFlush(bool do_flush=true);

        // Sets the logging level of this manager
        void setLogLevel(int log_level);
        // Returns the logging level of this manager
        int getLogLevel() const;

        // Invokes vfWriteLog with MAXINT as log_level
        int writeLog(const char *fmt, ...);
        // Write to logfile. Supports printf() formatting of strings
        // Returns number of bytes written. -1 if error
        int writeLog(int log_level, const char *fmt, ...);

        static SDL_mutex *m_log_manager;
    };
} // End of namespace

#endif // __LOG_MANAGER_H__


