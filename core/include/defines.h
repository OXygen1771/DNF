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

// integer and boolean typedefs
#include <stdint.h>
#include <stdbool.h>
typedef bool bool8_t;

// float typedefs
typedef float float32_t;
typedef double float64_t;

// static assertions
#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

// ensure all typedefs are correct
STATIC_ASSERT(sizeof(uint8_t) == 1, "Expected uint8_t to be 1 byte");
STATIC_ASSERT(sizeof(uint16_t) == 2, "Expected uint16_t to be 2 bytes");
STATIC_ASSERT(sizeof(uint32_t) == 4, "Expected uint32_t to be 4 bytes");
STATIC_ASSERT(sizeof(uint64_t) == 8, "Expected uint64_t to be 8 bytes");

STATIC_ASSERT(sizeof(int8_t) == 1, "Expected int8_t to be 1 byte");
STATIC_ASSERT(sizeof(int16_t) == 2, "Expected int16_t to be 2 bytes");
STATIC_ASSERT(sizeof(int32_t) == 4, "Expected int32_t to be 4 bytes");
STATIC_ASSERT(sizeof(int64_t) == 8, "Expected int64_t to be 8 bytes");

STATIC_ASSERT(sizeof(float32_t) == 4, "Expected float32_t to be 4 bytes");
STATIC_ASSERT(sizeof(float64_t) == 8, "Expected float64_t to be 8 bytes");

STATIC_ASSERT(sizeof(bool) == 1, "Expected bool to be 1 byte");
STATIC_ASSERT(sizeof(bool8_t) == 1, "Expected bool8_t to be 1");

STATIC_ASSERT(true == 1, "Expected true to be 1");
STATIC_ASSERT(false == 0, "Expected false to be 0");


// exports
#ifdef DNFEXPORT
    #ifdef _MSC_VER
        #define DNF_API __declspec(dllexport)
    #else
        #define DNF_API __attribute__((visibility("default")))
    #endif
// imports
#else
    #ifdef _MSC_VER
        #define DNF_API __declspec(dllimport)
    #else
        #define DNF_API
    #endif
#endif
