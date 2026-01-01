// DNF (Doomed and Forgotten): a DOOM-style first-person shooter.
// Copyright (C) 2025-2026  Alexandr Gorbatenko
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#ifndef DNF_LOG_H
#define DNF_LOG_H

/**
 * @brief An enum that represents the current program logging level.
 */
typedef enum DNF_LogLevel
{
    DNF_LOG_NONE,

    DNF_LOG_TRACE,
    DNF_LOG_DEBUG,
    DNF_LOG_INFO,
    DNF_LOG_WARN,
    DNF_LOG_ERROR,
    DNF_LOG_FATAL,

    DNF_LOG_LEVEL_COUNT,  //!< Total count of logging levels
} DNF_LogLevel;

/**
 * @brief Initializes the logging system: opens a log file and resets the log
 * text buffer.
 */
void dnf_log_system_init(void);

/**
 * @brief Main logging function which handles all the logging levels.
 *
 * @param file Pointer to caller file.
 * @param line Line number of the logging call.
 * @param level Logging level, see DNF_LogType.
 * @param message Message of the log, a printf format string.
 * @param ... Additional arguments for the message format string.
 */
void dnf_log_message(const char *file, int line, DNF_LogLevel level, const char *message, ...);


// debug breaking for Windows
#if defined(_WIN32) && defined(_DEBUG)
    #define DNF_BREAKPOINT() __debugbreak()
#elif defined(_DEBUG)
    #define DNF_BREAKPOINT() __asm{ int 3 }  // asm breakpoint
#else
    #define DNF_BREAKPOINT()
#endif


// enable all logging levels when compiling in debug mode
// enable debug breaking on errors
#ifdef _DEBUG
#define dnf_trace(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_TRACE, fmt, ##__VA_ARGS__)
#define dnf_debug(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_DEBUG, fmt, ##__VA_ARGS__)
#define dnf_info(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_INFO, fmt, ##__VA_ARGS__)
#define dnf_warn(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_WARN, fmt, ##__VA_ARGS__)
#define dnf_error(fmt, ...) { dnf_log_message(__FILE__, __LINE__, DNF_LOG_ERROR, fmt, ##__VA_ARGS__); DNF_BREAKPOINT(); }
#define dnf_fatal(fmt, ...) { dnf_log_message(__FILE__, __LINE__, DNF_LOG_FATAL, fmt, ##__VA_ARGS__); DNF_BREAKPOINT(); }

#else
#define dnf_trace(fmt, ...) {}
#define dnf_debug(fmt, ...) {}
#define dnf_info(fmt, ...) {}
#define dnf_warn(fmt, ...) {}
#define dnf_error(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_ERROR, fmt, ##__VA_ARGS__)
#define dnf_error(fmt, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_FATAL, fmt, ##__VA_ARGS__)
#endif


#endif //DNF_LOG_H
