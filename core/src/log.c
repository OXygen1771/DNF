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


#include "log.h"

#include <stdio.h>

// use localtime_s instead of localtime: C4996
#define __STDC_WANT_LIB_EXT1__ 1 // NOLINT(*-reserved-identifier)
#include <time.h>

// platform-specific
#ifdef _WIN32
#include <windows.h>  // CreateFile(), WriteFile(), CloseHandle()
#else
#include <unistd.h>    // write()
#include <fnctl.h>     // open() file creation flags
#include <sys/stat.h>  // open() file permission flags
#endif


#define DNF_LOG_BUFFER_SIZE (1024 * 4)           // 4KB buffer
#define DNF_LOG_FILENAME "dnf_game.log"
#define DNF_LOG_MAX_MESSAGE_LENGTH (1024 - 256)  // max message length to fit in buffer
#define DNF_LOG_MAX_LINE_LENGTH (DNF_LOG_MAX_MESSAGE_LENGTH + 256)  // max formatted line length

static char log_buffer[DNF_LOG_BUFFER_SIZE];
static size_t log_buffer_pos = 0;

// file handle/descriptor
#ifdef _WIN32
static HANDLE dnf_log_handle = INVALID_HANDLE_VALUE;
#else
static int dnf_log_fd = -1;
#endif

// log level names, they mirror those defined in DNF_LogLevel
static const char* dnf_log_level_names[DNF_LOG_LEVEL_COUNT] = {
    "NONE",
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

// global minimum logging level
static DNF_LogLevel global_log_level = DNF_LOG_DEBUG;

// flag to indicate if the logger is initialized yet
static boolean is_logger_initialized = FALSE;


// -- Helper functions

/**
 * @brief Opens a file to write logs to. Sets the static handle (if on Windows)
 * or file descriptor (if not on Windows) variable.
 *
 * @param filename Filename of the file to be created.
 */
static void dnf_log_open_file(const char *filename)
{
    #ifdef _WIN32
    dnf_log_handle = CreateFileA(
        filename,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (dnf_log_handle == INVALID_HANDLE_VALUE)
        fprintf(
            stderr,
            "[ERROR]: Failed to open log file %s (WINDOWS ERROR %lu)\n",
            filename, GetLastError());
    #else
    dnf_log_fd = open(
        filename,
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR);
    if (dnf_log_fd == -1)
        perror("[ERROR]: Failed to open log file. Will not log to any file.");
    #endif
}

/**
 * @brief Forcefully closes the log file.
 */
static void dnf_log_close_file(void)
{
    #ifdef _WIN32
    if (dnf_log_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(dnf_log_handle);
        dnf_log_handle = INVALID_HANDLE_VALUE;
    }
    #else
    if (dnf_log_fd != -1)
    {
        close(dnf_log_fd);
        dnf_log_fd = -1;
    }
    #endif
    printf("[INFO]: File %s closed successfully.\n", DNF_LOG_FILENAME);
}

/**
 * @brief Flushes the logging buffer to the log file.
 */
static void dnf_log_flush_buffer(void)
{
    // buffer is empty
    if (log_buffer_pos == 0)
        return;

    #ifdef _WIN32
    DWORD bytes_written = 0;
    if (dnf_log_handle != INVALID_HANDLE_VALUE)
        WriteFile(dnf_log_handle, log_buffer, (DWORD)log_buffer_pos, &bytes_written, NULL);
    #else
    if (dnf_log_fd != -1)
        write(dnf_log_fd, log_buffer, log_buffer_pos);
    #endif

    // reset buffer pos
    log_buffer_pos = 0;
}

/**
 * @brief Shuts down the logging system: flushes buffers and closes files.
 */
static void dnf_log_system_close(void)
{
    // logger not yet initialized = don't need to do anything
    if (!is_logger_initialized)
        return;

    // flush buffer
    if (log_buffer_pos > 0)
        dnf_log_flush_buffer();
    // close file
    dnf_log_close_file();
    is_logger_initialized = FALSE;
    printf("[INFO]: Logging system shut down successfully.\n");
}

void dnf_log_system_init(void)
{
    // logger already initialized - don't need to do it again
    if (is_logger_initialized)
        return;

    // open file, reset buffer, set flag
    dnf_log_open_file(DNF_LOG_FILENAME);
    memset(log_buffer, 0, DNF_LOG_BUFFER_SIZE);
    log_buffer_pos = 0;
    is_logger_initialized = TRUE;

    // register shutdown callback
    atexit(dnf_log_system_close);
}


// -- Main function
void dnf_log_message(
    const char *file,
    int line,
    DNF_LogLevel level,
    const char *message,
    ...)
{
    if (level < global_log_level)
        return;

    // time formatting
    time_t timer;
    struct tm tm_info;
    char time_buffer[32];
    time(&timer);
    localtime_s(&tm_info, &timer);  // C4996: use this instead of localtime()
    strftime(time_buffer, 32, "%Y-%m-%d %H:%M:%S", &tm_info);

    // formatting user's message
    char formatted_message[DNF_LOG_MAX_MESSAGE_LENGTH];
    va_list args;
    va_start(args, message);
    vsnprintf_s(  // C4996: use this instead of vsnprintf()
        formatted_message,
        DNF_LOG_MAX_MESSAGE_LENGTH,
        DNF_LOG_MAX_LINE_LENGTH,
        message,
        args);
    va_end(args);

    // full log line
    char log_line[DNF_LOG_MAX_LINE_LENGTH];
    const int len = snprintf(
        log_line,
        DNF_LOG_MAX_LINE_LENGTH,
        "%s - [%s]:[%s:%d]: %s\n",
        time_buffer, dnf_log_level_names[level], file, line, formatted_message
        );

    // print to stream (stdout/stderr)
    fprintf(level > DNF_LOG_ERROR ? stderr : stdout, "%s", log_line);

    // print to log file
    // no space left in buffer - flush buffer first
    if (len >= DNF_LOG_BUFFER_SIZE || log_buffer_pos + len >= DNF_LOG_BUFFER_SIZE)
        dnf_log_flush_buffer();

    // add line to buffer and move buffer pos
    memcpy(log_buffer + log_buffer_pos, log_line, len);
    log_buffer_pos += len;
}
