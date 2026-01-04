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


#include "logger.h"

#include <raylib.h>  // cross-platform file operations

#include <stdio.h>   // message formatting and console output
#include <time.h>    // time formatting
#include <string.h>  // memset

// A bad practice!
#define DNF_LOG_BUFFER_SIZE 32768
// Another bad practice! It is OK for now, though.
#define DNF_LOG_FILENAME "dnf_game.log"
// And yet another bad practice!
#define DNF_LOG_MAX_MSG_LENGTH 8192

static char log_buffer[DNF_LOG_BUFFER_SIZE];  // Log buffer.
static size_t log_buffer_pos = 0;  // Last character in the log buffer.

// Names of logging levels.
static const char* log_level_names[DNF_LOG_LEVEL_COUNT] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};


/**
 * @brief Flushes the log buffer to the specified log file, then resets
 * log_buffer_pos to 0.
 *
 * @param filename Name of the log file.
 *
 * @return True if the file write was successful.
 */
static bool8_t flush_log_buffer_to_file(const char *filename)
{
    // no need to flush
    if (log_buffer_pos == 0)
        return true;

    if (!SaveFileData(filename, log_buffer, (int32_t)log_buffer_pos))
        return false;

    log_buffer_pos = 0;
    return true;
}

bool8_t dnf_logger_init(void)
{
    // create log file if it doesn't exist
    if (!DirectoryExists("./logs"))
        if (MakeDirectory("./logs") != 0)
            return false;
    return true;
}

void dnf_logger_shutdown(void)
{
    flush_log_buffer_to_file("./logs/"DNF_LOG_FILENAME);
}

void dnf_log_message(const char* file, const uint32_t line, const dnf_log_level level, const char* message, ...)
{
    const bool8_t is_error = level > DNF_LOG_LEVEL_WARN;

    // message formatted with given args
    char formatted_message[DNF_LOG_MAX_MSG_LENGTH] = {0};

    // time formatting
    time_t timer;
    struct tm tm_info;
    char time_buffer[32];
    time(&timer);
    localtime_s(&tm_info, &timer);
    strftime(time_buffer, 32, "%Y-%m-%d %H:%M:%S", &tm_info);

    // pasting in variadic arguments
    va_list arg_ptr = nullptr;
    va_start(arg_ptr, message);
    vsnprintf(formatted_message, DNF_LOG_MAX_MSG_LENGTH, message, arg_ptr);
    va_end(arg_ptr);

    // full log line
    char out_message[DNF_LOG_MAX_MSG_LENGTH];
    const uint32_t message_len = sprintf_s(
        out_message,
        DNF_LOG_MAX_MSG_LENGTH,
        "%s - [%s] in (%s:%d): %s\n",
        time_buffer, log_level_names[level], file, line, formatted_message);

    // print to stdout/stderr (should work on Windows and Linux?)
    if (is_error)
        fprintf(stderr, "%s", out_message);
    else
        fprintf(stdout, "%s", out_message);

    // flush buffer if overflown
    if (message_len >= DNF_LOG_MAX_MSG_LENGTH || log_buffer_pos + message_len >= DNF_LOG_BUFFER_SIZE)
        flush_log_buffer_to_file("./logs/"DNF_LOG_FILENAME);
    else
    {
        memcpy(log_buffer + log_buffer_pos, out_message, message_len);
        log_buffer_pos += message_len;
    }
}
