#  Copyright (C) 2021 realth000 <a598919335@gmail.com>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13)

project(BackTook
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(src)

# Version settings
if(WIN32)
    add_definitions(-DBACKTOOK_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
    add_definitions(-DBACKTOOK_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
    add_definitions(-DBACKTOOK_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH})
    add_definitions(-DBACKTOOK_VERSION_BUILD=1)
    add_definitions(-DBACKTOOK_VERSION_STRING="${PROJECT_VERSION}")
endif()

# Compile options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
endif()

include_directories(src)
include_directories(src/include)

if(WIN32)
    add_executable(BackTook WIN32)
else()
    add_executable(BackTook)
endif()

add_subdirectory(src)

target_link_libraries(BackTook PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
