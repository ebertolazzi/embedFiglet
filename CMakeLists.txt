############################################################################
#                                                                          #
#  file: CMakeLists.txt                                                    #
#  Copyright (C) 2016                                                      #
#      Enrico Bertolazzi                                                   #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      <mailto:enrico.bertolazzi@unitn.it>                                 #
#                                                                          #
############################################################################

cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# set(CMAKE_INSTALL_MESSAGE NEVER)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(ENABLE_CTEST)
  enable_testing()
endif()

# get version from the git tag
execute_process(COMMAND git describe --tags --abbrev=0 OUTPUT_VARIABLE VERSION)
string(REGEX REPLACE "\n$" "" VERSION "${VERSION}")

project(
  embedFiglet
  VERSION ${VERSION}
)

# NOTE: Predictable target name
set(STATIC_PROJECT "${PROJECT_NAME}Static")
set(DYNAMIC_PROJECT "${PROJECT_NAME}")

include(./CMakeLists-cflags.txt)
include(./CMakeUtilities.txt)


# Evaluating the suffix to append to target built by this CMake file
ebertolazzi_artifacts_suffix(ARTIFACTS_STATIC_SUFFIX TRUE)
if(BUILD_SHARED)
  ebertolazzi_artifacts_suffix(ARTIFACTS_DYNAMIC_SUFFIX FALSE)
endif()

include_directories(lib3rd/include)

message( STATUS "Compiler used: ${CMAKE_CXX_COMPILER_ID}")
set(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_C_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS_DEBUG})

set( SOURCES )
file( GLOB S ./src/*.cc )
foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach(F ${S})

set( HEADERS )
file( GLOB S ./src/*.h* )
foreach (F ${S})  
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND HEADERS ${RF} )
endforeach(F ${S})


add_library(${STATIC_PROJECT} STATIC ${SOURCES})
target_include_directories(
  ${STATIC_PROJECT} PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)
set_target_properties(
  ${STATIC_PROJECT} PROPERTIES
  OUTPUT_NAME "${PROJECT_NAME}${ARTIFACTS_STATIC_SUFFIX}"
  # FIXME: I'm not sure if this is required for OSX Framework
  #PUBLIC_HEADER "${HEADERS}"
  POSITION_INDEPENDENT_CODE ON
)

if ( NOT ( "${DEPEND_TARGETS}" STREQUAL "" ) )
  add_dependencies( ${STATIC_PROJECT} ${DEPEND_TARGETS} )
endif()

if(BUILD_SHARED)
  add_library(${DYNAMIC_PROJECT} SHARED ${SOURCES})
  set_target_properties(
    ${DYNAMIC_PROJECT} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}${ARTIFACTS_DYNAMIC_SUFFIX}"
    # FIXME: I'm not sure if this is required for OSX Framework
    # PUBLIC_HEADER "${HEADERS}"
    POSITION_INDEPENDENT_CODE ON
  )
  target_include_directories(
    ${DYNAMIC_PROJECT} PUBLIC 
    "$<BUILD_INTERFACE:${Clothoids_DIR}>"
    "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
  )
  if(WIN32)
    set_target_properties(
      ${DYNAMIC_PROJECT} PROPERTIES 
      WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )
  endif()
endif()


if(BUILD_EXECUTABLE OR ENABLE_CTEST)
  enable_testing()
  set(TEST_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set(
    EXECUTABLES 
    test
    example 
  )
  foreach(EXE ${EXECUTABLES})
    add_executable(${EXE} tests-cpp/${EXE}.cc)
    target_link_libraries(${EXE} PRIVATE ${STATIC_PROJECT} ${CMAKE_DL_LIBS})
    set_target_properties(
      ${EXE} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}"
    )
    add_test(${EXE} "${CMAKE_CURRENT_SOURCE_DIR}/bin/${EXE}")
  endforeach()
endif()

# INSTALL TARGETS
set(INSTALL_TARGETS ${STATIC_PROJECT})
if(BUILD_SHARED)
  set(INSTALL_TARGETS ${INSTALL_TARGETS} ${DYNAMIC_PROJECT})
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeInstall.txt")

message(STATUS "Using ${SSE_FLAGS} extensions")
message(STATUS "C compiler                  = ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler                = ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE     = ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS             = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_RELEASE       = ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_C_FLAGS               = ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_SYSTEM_NAME           = ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR      = ${CMAKE_SYSTEM_PROCESSOR}")
if(APPLE)
  message(STATUS "CMAKE_OSX_SYSROOT           = ${CMAKE_OSX_SYSROOT}")
  message(STATUS "CMAKE_OSX_ARCHITECTURES     = ${CMAKE_OSX_ARCHITECTURES}")
  message(STATUS "CMAKE_OSX_DEPLOYMENT_TARGET = ${CMAKE_OSX_DEPLOYMENT_TARGET}")
endif()
message(STATUS "BUILD_EXECUTABLE            = ${BUILD_EXECUTABLE}")
message(STATUS "SOURCES = ${SOURCES}")
message(STATUS "HEADERS = ${HEADERS}")
