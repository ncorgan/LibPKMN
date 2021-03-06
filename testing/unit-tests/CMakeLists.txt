#
# Copyright (c) 2016 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

IF(PKMN_ENABLE_QT)
    CMAKE_POLICY(SET CMP0020 NEW)
ENDIF()

INCLUDE(PKMNUnitTest)

# Find dependencies and set subcomponents
PKMN_APPEND_SUBCOMPONENT("C++ Tests")

IF(PKMN_ENABLE_C)
    PKMN_APPEND_SUBCOMPONENT("C Tests")
ENDIF()

IF(PKMN_ENABLE_CSHARP)
    FIND_PACKAGE(NUnit)
    PKMN_APPEND_SUBCOMPONENT("C# Tests")
ENDIF()

ADD_SUBDIRECTORY(pkmntest)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/pkmntest/include
)

#
# C++ tests
#
ADD_SUBDIRECTORY(cpp)

#
# C tests
#
IF(PKMN_ENABLE_C)
    ADD_SUBDIRECTORY(c)
ENDIF()

#
# C# tests
#
IF(PKMN_ENABLE_CSHARP)
    ADD_SUBDIRECTORY(csharp)
ENDIF()

#
# Lua tests
#
IF(PKMN_ENABLE_LUA)
    ADD_SUBDIRECTORY(lua)
ENDIF()

#
# Python tests
#
IF(PKMN_ENABLE_PYTHON)
    ADD_SUBDIRECTORY(python)
ENDIF()

#
# Ruby tests
#
IF(PKMN_ENABLE_RUBY)
    ADD_SUBDIRECTORY(ruby)
ENDIF()
