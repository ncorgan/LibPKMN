#
# Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

########################################################################
# CMake configuration
########################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
PROJECT(pkmn-cpp-app CXX)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules;${CMAKE_MODULE_PATH}")

########################################################################
# Find LibPKMN
########################################################################
FIND_PACKAGE(PKMN REQUIRED)

########################################################################
# Configure build
########################################################################
INCLUDE_DIRECTORIES(${PKMN_INCLUDE_DIR})
    
IF(CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall -Wextra -Werror -fvisibility=hidden")
ENDIF()

ADD_EXECUTABLE(pkmn-cpp-app pkmn-cpp-app.cpp)
TARGET_LINK_LIBRARIES(pkmn-cpp-app ${PKMN_LIBRARY})
