#
# Copyright (c) 2016-2018 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

########################################################################
# This file creates the following macros (example usage at end):
#
# SWIG_CSHARP_INIT:         Set the variables needed by later macros.
#
# SWIG_BUILD_CSHARP_MODULE: Build a C# SWIG module and install it in
#                           the desired location.
#
# Parameters:
#  * swig_filename:      The top-level .i file, minus the extension
#  * nativelib_name:     The name for the native library providing the SWIG layer
#                        (minus any prefix or suffix)
#  * csharp_module_name: The C# class associated with the module.
#  * cplusplus:          TRUE or FALSE, whether or not this is a C++ module.
#  * namespace:          The C# namespace this class will be in.
#
# Assumes the following variables are set:
#  * SWIG_MODULE_DIR:          The source directory that contains the .i
#                              file. This is needed so the .i file can
#                              include other local .i files.
#
#  * SWIG_CSHARP_INCLUDE_DIRS: C/C++ include directories needed by the
#                              source files.
#
#  * SWIG_CSHARP_LIBRARIES:    C/C++ libraries the C# module should
#                              link against.
#
#  * SWIG_CSHARP_FLAGS:        Flags to pass into the SWIG command (optional).
#
# CSHARP_BUILD_DLL: Build a C# DLL. Meant to be used after the
#                   previous macro.
#
# Parameters:
#  * dll_name: the name of the DLL to be produced (no extension)
#  * swig_modules: SWIG modules made with SWIG_BUILD_CSHARP_MODULE
#
# CSHARP_BUILD_EXE: Build a C# program. Meant to be used after the
#                   previous macro.
#
# Parameters:
#  * exe_name: program name (no extension)
#  * swig_dll: SWIG-generated C# DLL to be used as a reference
#
# Example (mymodule1.i, mymodule2.i):
#  * In CMake:
#        SWIG_BUILD_CSHARP_MODULE(mymodule1 mymodule1 MyModule1 TRUE)
#        SWIG_BUILD_CSHARP_MODULE(mymodule2 mymodule2 MyModule2 TRUE)
#        CSHARP_BUILD_DLL(mymodule.dll "mymodule1;mymodule2")
#
#  * From C#:
#        MyModule1.FunctionName()
#        MyModule2.FunctionName()
########################################################################

MACRO(SWIG_CSHARP_INIT)
    SET(CSHARP_SOURCE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CSharpSources)
    SET(CMAKE_SWIG_OUTDIR       ${CSHARP_SOURCE_DIRECTORY})
    FILE(MAKE_DIRECTORY         ${CSHARP_SOURCE_DIRECTORY})
    SET(CSHARP_BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
ENDMACRO(SWIG_CSHARP_INIT)

MACRO(SWIG_BUILD_CSHARP_MODULE swig_filename nativelib_name csharp_module_name cplusplus namespace)
    INCLUDE(UseCSharp)
    INCLUDE(UseSWIG)

    SET(SWIG_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SWIG_MODULE_DIR}
        ${SWIG_CSHARP_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/csharp
    )
    INCLUDE_DIRECTORIES(${SWIG_INCLUDE_DIRS})
    SET(SWIG_LIBRARIES ${SWIG_CSHARP_LIBRARIES})

    # Set output directory
    FOREACH(CMAKE_CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        STRING(TOUPPER ${CMAKE_CONFIGURATION_TYPE} CMAKE_CONFIGURATION_TYPE)
        SET_TARGET_PROPERTIES(${SWIG_MODULE_${nativelib_name}_TARGET_NAME}
            PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CSHARP_BINARY_DIRECTORY}")
        SET_TARGET_PROPERTIES(${SWIG_MODULE_${nativelib_name}_TARGET_NAME}
            PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} "${CSHARP_BINARY_DIRECTORY}")
    ENDFOREACH()

    # Set flags to pass into SWIG call
    IF(MSVC)
        SET(dllimport_name "${nativelib_name}")
    ELSE()
        SET(dllimport_name "lib${nativelib_name}")
    ENDIF()
    SET(CMAKE_SWIG_FLAGS -module ${csharp_module_name} -dllimport ${dllimport_name} -namespace ${namespace} ${CMAKE_SWIG_GLOBAL_FLAGS} ${CMAKE_GLOBAL_FLAGS})
    FOREACH(dir ${SWIG_INCLUDE_DIRS})
        LIST(APPEND CMAKE_SWIG_FLAGS "-I${dir}")
    ENDFOREACH(dir ${SWIG_INCLUDE_DIRS})

    # Allows CMake variables to be placed in SWIG .i files
    CONFIGURE_FILE(
        ${SWIG_MODULE_DIR}/${swig_filename}.i
        ${CMAKE_CURRENT_BINARY_DIR}/${swig_filename}.i
    @ONLY)

    # Set SWIG's C++ flag if specified by the user
    IF(${cplusplus})
        SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/${swig_filename}.i PROPERTIES CPLUSPLUS ON)
    ENDIF(${cplusplus})

    # The actual CMake call for SWIG
    SET(SWIG_MODULE_RC_NAME ${csharp_module_name})
    SWIG_ADD_MODULE(${nativelib_name} csharp ${CMAKE_CURRENT_BINARY_DIR}/${swig_filename}.i)
    LIST(LENGTH SWIG_LIBRARIES num_swig_libs)
    IF(${num_swig_libs} GREATER 0)
        SWIG_LINK_LIBRARIES(${nativelib_name} ${SWIG_LIBRARIES})
    ENDIF(${num_swig_libs} GREATER 0)

    SET_TARGET_PROPERTIES(${SWIG_MODULE_${nativelib_name}_REAL_NAME}
        PROPERTIES COMPILE_FLAGS "${PKMN_CXX_FLAGS}"
    )
    ADD_DEPENDENCIES(${SWIG_MODULE_${nativelib_name}_REAL_NAME}
        pkmn_csharp_docs
        csharp_CamelCase_i
    )

    # Install files
    IF(WIN32)
        INSTALL(
            TARGETS ${SWIG_MODULE_${nativelib_name}_REAL_NAME}
            DESTINATION bin
            COMPONENT CSharp
        )
    ELSE()
        INSTALL(
            TARGETS ${SWIG_MODULE_${nativelib_name}_REAL_NAME}
            DESTINATION lib
            COMPONENT CSharp
        )
    ENDIF(WIN32)
ENDMACRO(SWIG_BUILD_CSHARP_MODULE)

MACRO(CSHARP_BUILD_DLL dll_name swig_modules)
    CSHARP_ADD_LIBRARY(
        ${dll_name} "${CMAKE_SWIG_OUTDIR}/*.cs"
    )
    ADD_DEPENDENCIES(${dll_name} ${swig_modules})

    INSTALL(
        FILES ${CSHARP_BINARY_DIRECTORY}/${dll_name}.dll
        DESTINATION bin
        COMPONENT CSharp
    )
ENDMACRO(CSHARP_BUILD_DLL)

MACRO(CSHARP_BUILD_EXE exe_name swig_dll)
    CSHARP_ADD_EXECUTABLE(${exe_name} ${CSHARP_SOURCE_DIRECTORY}/${exe_name}.cs ${CMAKE_CURRENT_BINARY_DIR}/${swig_dll}.dll)
    ADD_DEPENDENCIES(${exe_name} ${swig_dll})

    INSTALL(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}
        DESTINATION bin
        COMPONENT CSharp
    )
ENDMACRO(CSHARP_BUILD_EXE)
