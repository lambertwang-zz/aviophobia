/*
 * Log manager class
 */

// c++ standard libraries
#include <limits.h>

// Dragonfly headers
#include "LogManager.h"
#include "GameManager.h"
#include "utility.h"

av::LogManager::LogManager() {
}


av::LogManager &av::LogManager::getInstance() {
    static av::LogManager log_manager;
    return log_manager;
}

void av::LogManager::setFlush(bool do_flush) {
    this->do_flush = do_flush;
}

// Invokes writeLog with INT_MAX as log_level
int av::LogManager::writeLog(const char *fmt, ...) {
    
    // Convert stringformat to a string
    char char_format[1024];
    
    va_list args;
    va_start(args, fmt);
    fflush(stderr);
#if defined _WIN32 || defined _WIN64
    vsprintf_s(char_format, fmt, args);
#else
    vsprintf(char_format, fmt, args);
#endif
    fflush(stderr);
    va_end(args);

    // pass string through
    int return_val = this->writeLog(INT_MAX, "%s", char_format);

    return return_val;
}

// Returns number of characters including escape codes and excluding the timestring
int av::LogManager::writeLog(int log_level, const char *fmt, ...) {
    if (log_level >= this->log_level) {
        if (this->p_f && this->isStarted()) {
            // Print timestring and frame number to log file
            av::GameManager &game_manager = av::GameManager::getInstance();
            fprintf(p_f, "%8s  %6d  ", av::getTimeString(), game_manager.getStepCount());

            // Format arguments
            va_list args;
            va_start(args, fmt);
            int chars_printed = vfprintf(p_f, fmt, args);
            va_end(args);

            // Add newline to log file
            fprintf(p_f, "\n");
            
            // Flush log file is specified to do so
            if (this->do_flush) {
                fflush(p_f);
            }

            return chars_printed;
        }
    }
    return -1;
}

void av::LogManager::setLogLevel(int log_level) {
    this->log_level = log_level;
    this->writeLog(2, "av::LogManager::setLogLevel(): Log level set to %d.", log_level);
}

int av::LogManager::getLogLevel() const {
    return this->log_level;
}

// Virtual functions
av::LogManager::~LogManager() {
    this->shutDown();
}

int av::LogManager::startUp() {
    return this->startUp(INT_MAX);
}

int av::LogManager::startUp(int log_level) {
    if (!this->isStarted()) {
        av::Manager::startUp();
        // Set member parameters
        this->setType("LOG_MANAGER");
        this->setLogLevel(log_level);
        
        // Attempt to delete previous logfile
        remove(av::LOGFILE_NAME.c_str());
        
        // Open "dragonfly.log", makes the file if it doesn't exist
#if defined _WIN32 || defined _WIN64
        fopen_s(&(this->p_f), av::LOGFILE_NAME.c_str(), "w");
#else
        this->p_f = fopen(av::LOGFILE_NAME.c_str(), "w");
#endif
        if (!this->p_f) {
            this->writeLog(2, "av::LogManager::startUp(): Problem opening file %s", av::LOGFILE_NAME.c_str());
            av::Manager::shutDown();
            return -1;
        }

        this->writeLog(2, "av::LogManager::startUp(): LogManager started.");
        return 0;
    }
    return -1;
}

void av::LogManager::shutDown() {
    if (this->isStarted()) {
        this->writeLog(2, "av::LogManager::shutDown(): Closing LogManager");
        // Close dragonfly.log file if it is open
        if (this->p_f) {
            this->writeLog(1, "av::LogManager::shutDown(): Closing %s", av::LOGFILE_NAME.c_str());
            fclose(this->p_f);
        }
        av::Manager::shutDown();

    }
}

