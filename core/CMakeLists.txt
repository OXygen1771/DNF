# DNF (Doomed and Forgotten): a DOOM-style first-person shooter.
# Copyright (C) 2025  Alexandr Gorbatenko
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

add_library(core STATIC)

target_sources(core
        PRIVATE
            src/engine.c
            src/renderer.c
            src/input_system.c
            src/log.c

        PUBLIC
            FILE_SET HEADERS
            FILES
                include/engine.h
                include/renderer.h
                include/input_system.h
                include/log.h
)

target_include_directories(core
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
)

target_link_libraries(core
        PUBLIC
            raylib  # from root CMakeLists.txt
)
