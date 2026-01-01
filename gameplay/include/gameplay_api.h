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


#ifndef DNF_GAMEPLAY_API_H
#define DNF_GAMEPLAY_API_H

#ifdef _WIN32  // link shared gameplay library on MSVC
    #ifdef DNF_GAMEPLAY_EXPORTS
        #define DNF_GAMEPLAY_API __declspec(dllexport)
    #else
        #define DNF_GAMEPLAY_API __declspec(dllimport)
    #endif
#else // Linux etc.
    #define DNF_GAMEPLAY_API
#endif

#endif //DNF_GAMEPLAY_API_H
