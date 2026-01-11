# DNF (Doomed and Forgotten): a DOOM-style first-person shooter.
# Copyright (C) 2025-2026  Alexandr Gorbatenko
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

# hot-loadable (in the future) game code
add_library(game SHARED)

target_sources(game
        PRIVATE
            src/game.c
            src/game_render.c

        PUBLIC
            FILE_SET HEADERS
            FILES
                include/game.h
                include/game_render.h
                include/map_data.h
)

include_directories(./include)

target_link_libraries(game
        PRIVATE
            core
)


# simple game launch .exe
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
            src/entrypoint.c

        PRIVATE
            FILE_SET HEADERS
            FILES
                include/entrypoint.h
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            game
            core
)
