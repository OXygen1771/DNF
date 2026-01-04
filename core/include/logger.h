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


#pragma once

#include "defines.h"

#define DNF_LOG_TRACE_ENABLED 1
#define DNF_LOG_DEBUG_ENABLED 1
#define DNF_LOG_INFO_ENABLED 1
#define DNF_LOG_WARN_ENABLED 1
// NOTE: ERROR and FATAL are always enabled

/**
 * @brief An enum that represents the current program logging level.
 */
typedef enum dnf_log_level
{
    DNF_LOG_LEVEL_TRACE = 0,  //!< In-depth debugging app info.
    DNF_LOG_LEVEL_DEBUG = 1,  //!< All-purpose debugging app info.
    DNF_LOG_LEVEL_INFO = 2,   //!< Basic app info.
    DNF_LOG_LEVEL_WARN = 3,   //!< App will recover from this state.
    DNF_LOG_LEVEL_ERROR = 4,  //!< App could recover from this state.
    DNF_LOG_LEVEL_FATAL = 5,  //!< App cannot continue running.

    DNF_LOG_LEVEL_COUNT = 6,  //!< Total count of logging levels
} dnf_log_level;

/**
 * @brief Initializes the logging system.
 *
 * Creates a ./logs directory if it doesn't exist.
 */
bool8_t dnf_logger_init(void);

/**
 * @brief Shuts down the logging system.
 *
 * For now, does basically nothing.
 */
void dnf_logger_shutdown(void);

/**
 * @brief Main logging function to handle all logging output.
 *
 * @param file Name of the file where the message originates from.
 * @param line Number of line in the origin file.
 * @param level Logging level (as in dnf_log_level).
 * @param message Message format string.
 * @param ... Variadic arguments (format string parameters).
 */
DNF_API void dnf_log_message(const char *file, uint32_t line, dnf_log_level level, const char *message, ...);


#if DNF_LOG_TRACE_ENABLED == 1
    // Logs a tracing level message (in-depth debugging app info).
    #define DNF_TRACE(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
    // Logs a tracing level message (in-depth debugging app info).
    #define DNF_TRACE(message, ...)
#endif

#if DNF_LOG_DEBUG_ENABLED == 1
    // Logs a debug level message (all-purpose debugging app info).
    #define DNF_DEBUG(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
    // Logs a debug level message (all-purpose debugging app info).
    #define DNF_DEBUG(message, ...)
#endif

#if DNF_LOG_INFO_ENABLED == 1
    // Logs an information level message (basic app info).
    #define DNF_INFO(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
    // Logs an information level message (basic app info).
    #define DNF_INFO(message, ...)
#endif

#if DNF_LOG_WARN_ENABLED == 1
    // Logs a warning level message (app will recover from this state).
    #define DNF_WARN(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
    // Logs a warning level message (app will be able to recover from this state).
    #define DNF_WARN(message, ...)
#endif

// Logs an error level message (app could recover from this state).
#define DNF_ERROR(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

// Logs a fatal level message (app cannot continue running).
#define DNF_FATAL(message, ...) dnf_log_message(__FILE__, __LINE__, DNF_LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
