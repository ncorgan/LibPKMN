#
# Copyright (c) 2015-2016 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PKMN_SOURCE_DIR}/include
    ${PKMN_BINARY_DIR}/include
)

SET(pkmn_c_libs
    pkmn
)

#
# Add sources included in all builds
#

ADD_SUBDIRECTORY(calculations)
ADD_SUBDIRECTORY(database)
ADD_SUBDIRECTORY(utils)

SET(pkmn_c_sources
    ${pkmn_c_calculations_sources}
    ${pkmn_c_database_sources}
    ${pkmn_c_utils_sources}
    build_info.cpp
    cpp_to_c.cpp
    error.cpp
    item_bag.cpp
    item_list.cpp
)


#
# pkg-config file
#
FIND_PACKAGE(PkgConfig)
IF(PKG_CONFIG_FOUND)
    CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/pkmn-c.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/pkmn-c.pc
    @ONLY)
    INSTALL(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/pkmn-c.pc
        DESTINATION ${PKMN_LIBRARY_DIR}/pkgconfig
    )
ENDIF(PKG_CONFIG_FOUND)

#
# Add DLL resource file to Windows builds
#
IF(WIN32)
    IF(MINGW)
        SET(LIB_PREFIX "lib")
    ENDIF(MINGW)
    CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/pkmn-c.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/pkmn-c.rc
    @ONLY)
    SET(pkmn_rc ${CMAKE_CURRENT_BINARY_DIR}/pkmn-c.rc)
ENDIF(WIN32)

SET_SOURCE_FILES_PROPERTIES(${pkmn_c_sources}
    PROPERTIES COMPILE_FLAGS "${PKMN_CXX_FLAGS}"
)

ADD_LIBRARY(pkmn-c SHARED ${pkmn_c_sources} ${pkmn_c_rc})
TARGET_LINK_LIBRARIES(pkmn-c ${pkmn_c_libs})
SET_TARGET_PROPERTIES(pkmn-c PROPERTIES DEFINE_SYMBOL "PKMN_DLL_EXPORTS")

INSTALL(
    TARGETS pkmn-c
    LIBRARY DESTINATION ${PKMN_LIBRARY_DIR} COMPONENT Libraries # .so
    ARCHIVE DESTINATION ${PKMN_LIBRARY_DIR} COMPONENT Libraries # .lib
    RUNTIME DESTINATION ${PKMN_RUNTIME_DIR} COMPONENT Libraries # .dll
)