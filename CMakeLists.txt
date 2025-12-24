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
###          PROJECT EXECUTABLE          ###
############################################

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
            hello.c
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            raylib
)


############################################
###            BUILD SETTINGS            ###
############################################

set(CMAKE_C_FLAGS "-Wall -Wextra")
