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


cmake_minimum_required(VERSION 4.0)

project(
        DNF
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "A simple DOOM-like game in C"
)

set(CMAKE_C_STANDARD 23)

# prevent installing into system directories
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


############################################
### THIRD-PARTY LIBRARIES & DEPENDENCIES ###
############################################
include(FetchContent)  # use FetchContent to download and build dependencies
set(FETCHCONTENT_QUIET OFF)

function(add_dependency_from_git dependency_name git_url git_tag find_package_args)
    FetchContent_Declare(${dependency_name}
            GIT_REPOSITORY ${git_url}
            GIT_TAG ${git_tag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            FIND_PACKAGE_ARGS ${find_package_args}
    )
    FetchContent_MakeAvailable(${dependency_name})
    target_compile_options(${dependency_name} PRIVATE "-w")  # disable warnings for thirdparty libraries
endfunction()

### raylib ###
set(RAYLIB_VERSION 5.5)
set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build raylib examples" FORCE)
add_dependency_from_git(
        raylib
        https://github.com/raysan5/raylib.git
        c1ab645ca298a2801097931d1079b10ff7eb9df8  # 5.5
        ${RAYLIB_VERSION}
)


############################################
###        PROJECT SUBDIRECTORIES        ###
############################################

add_subdirectory(core)
add_subdirectory(gameplay)


############################################
###          PROJECT EXECUTABLE          ###
############################################

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            core
            gameplay
)


############################################
###            BUILD SETTINGS            ###
############################################


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif ()
