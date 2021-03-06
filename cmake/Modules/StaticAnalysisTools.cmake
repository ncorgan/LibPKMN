#
# Copyright (c) 20178 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

SET(PKMN_USE_CLANGTIDY "${PKMN_USE_CLANGTIDY}" CACHE BOOL "Enable Clang-tidy testing")
SET(PKMN_USE_IWYU "${PKMN_USE_IWYU}" CACHE BOOL "Enable Include-What-You-Use testing")

IF(PKMN_USE_CLANGTIDY)
    if(NOT CLANG_TIDY_EXECUTABLE)
        FIND_PROGRAM(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
    ENDIF()
    MESSAGE(STATUS "Using clang-tidy: ${CLANG_TIDY_EXECUTABLE}")

    SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    SET(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE}")
    SET(CLANG_TIDY_PROPERTY
        "${CLANG_TIDY_EXECUTABLE}"
        "-checks=\
         clang-diagnostic-*,\
         misc-macro-parentheses,\
         modernize-loop-convert,readability-else-after-return"
    )
ENDIF()

IF(PKMN_USE_IWYU)
    if(NOT IWYU_EXECUTABLE)
        FIND_PROGRAM(IWYU_EXECUTABLE NAMES include-what-you-use)
    ENDIF()
    MESSAGE(STATUS "Using Include-What-You-Use: ${IWYU_EXECUTABLE}")

    SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    SET(IWYU_PROPERTY "${IWYU_EXECUTABLE}")
ENDIF()
