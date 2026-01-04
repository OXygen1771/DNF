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

#define DNF_ASSERTIONS_ENABLED 1


// Debug breaking
#if DNF_ASSERTIONS_ENABLED == 1
    #if _MSC_VER
        #define debug_break() __debugbreak()
    #else
        #define debug_break() __builtin_trap()
    #endif


/**
 * @brief Reports an assertion failure.
 *
 * @param expression Literal expression which caused the failure.
 * @param file Name of the file where the message originates from.
 * @param line Number of line in the origin file.
 * @param message Assertion failure message (non-format).
 */
DNF_API void log_assertion_failure(const char *expression, const char *file, uint32_t line, const char *message);


// Assert without a displayed message.
#define DNF_ASSERT(expr)                                            \
    {                                                               \
        if (expr)                                                   \
        {}                                                          \
        else                                                        \
        {                                                           \
            log_assertion_failure(#expr, __FILE__, __LINE__, "");   \
            debug_break();                                          \
        }                                                           \
    }

// Assert and display a message.
#define DNF_ASSERT_MSG(expr, msg)                                    \
    {                                                                \
        if (expr)                                                    \
        {}                                                           \
        else                                                         \
        {                                                            \
            log_assertion_failure(#expr, __FILE__, __LINE__, msg);   \
            debug_break();                                           \
        }                                                            \
    }

// define a DNF_ASSERT_DEBUG which will only work if the _DEBUG flag is set
#ifdef _DEBUG
// Assert in debug mode without a displayed message.
#define DNF_ASSERT_DEBUG(expr)                                      \
    {                                                               \
        if (expr)                                                   \
        {}                                                          \
        else                                                        \
        {                                                           \
            log_assertion_failure(#expr, __FILE__, __LINE__, "");   \
            debug_break();                                          \
        }                                                           \
    }
#else
#define DNF_ASSERT_DEBUG(expr)  // Does nothing if the flag _DEBUG is not set.
#endif

#else
#define DNF_ASSERT(expr)           // Does nothing if assertions are disabled.
#define DNF_ASSERT_MSG(expr, msg)  // Does nothing if assertions are disabled.
#define DNF_ASSERT_DEBUG(expr)     // Does nothing if assertions are disabled.

#endif
