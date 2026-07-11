############################################################################
#                                                                          #
#  embedFiglet -- standalone CMake build, no cmake_utils submodule.         #
#                                                                          #
############################################################################

cmake_minimum_required(VERSION 3.16)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.31)
  cmake_policy(SET CMP0177 NEW)
endif()
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Version from Git tag when available.
find_package(Git QUIET)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE EMBED_FIGLET_PROJECT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(EMBED_FIGLET_PROJECT_VERSION MATCHES "^v")
    string(SUBSTRING "${EMBED_FIGLET_PROJECT_VERSION}" 1 -1 EMBED_FIGLET_PROJECT_VERSION)
  endif()
endif()
if(NOT EMBED_FIGLET_PROJECT_VERSION)
  set(EMBED_FIGLET_PROJECT_VERSION "1.0.0")
endif()

project(
  embedFiglet
  VERSION ${EMBED_FIGLET_PROJECT_VERSION}
  HOMEPAGE_URL "https://ebertolazzi.github.io/embedFiglet/"
  LANGUAGES CXX
)

include(GNUInstallDirs)
include(CTest)

option(UTILS_GIT_VERSION "Get version from Git command" ON)
option(UTILS_ENABLE_TESTS "Enable compilation of testing targets" OFF)
option(UTILS_BUILD_SHARED "Enable shared library compilation" OFF)
option(UTILS_INSTALL_LOCAL "Enable installation into local lib directory" ON)
option(UTILS_TWEAK_VERSION_IS_TIMESTAMP "Set tweak version to timestamp" OFF)
option(BUILD_SHARED "Compatibility alias for UTILS_BUILD_SHARED" ${UTILS_BUILD_SHARED})
option(BUILD_EXECUTABLE "Compatibility alias for building tests/examples" OFF)

if(BUILD_SHARED AND NOT UTILS_BUILD_SHARED)
  set(UTILS_BUILD_SHARED ON CACHE BOOL "Enable shared library compilation" FORCE)
endif()

set(UTILS_NAMESPACE "utils" CACHE STRING "Namespace prefix used for compatibility targets")

if(PROJECT_IS_TOP_LEVEL AND (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local"))
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/lib" CACHE PATH "Install prefix" FORCE)
endif()
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Install include directory" FORCE)
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Install library directory" FORCE)
set(CMAKE_INSTALL_BINDIR "bin" CACHE PATH "Install binary directory" FORCE)

file(MAKE_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin"
  "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(APPLE)
  set(EMBED_FIGLET_PLATFORM_SUFFIX osx)
elseif(WIN32)
  if(MINGW)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(EMBED_FIGLET_PLATFORM_SUFFIX mingw64)
    else()
      set(EMBED_FIGLET_PLATFORM_SUFFIX mingw32)
    endif()
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(EMBED_FIGLET_PLATFORM_SUFFIX win64)
  else()
    set(EMBED_FIGLET_PLATFORM_SUFFIX win32)
  endif()
elseif(UNIX)
  set(EMBED_FIGLET_PLATFORM_SUFFIX linux)
else()
  string(TOLOWER "${CMAKE_SYSTEM_NAME}" EMBED_FIGLET_PLATFORM_SUFFIX)
endif()

if(APPLE)
  execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_OSX_ARCHITECTURES ${ARCHITECTURE})
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/../CMakeLists-customize.txt")
  include("${CMAKE_CURRENT_LIST_DIR}/../CMakeLists-customize.txt")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-poison-system-directories>"
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-switch-default>"
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-exit-time-destructors>"
  )
endif()

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE EMBED_FIGLET_SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cc")
list(FILTER EMBED_FIGLET_SOURCES EXCLUDE REGEX ".*hsl_fake\\.cc$")

file(GLOB_RECURSE EMBED_FIGLET_PUBLIC_HEADERS CONFIGURE_DEPENDS
  "${SOURCE_DIR}/*.h"
  "${SOURCE_DIR}/*.hh"
  "${SOURCE_DIR}/*.hpp"
  "${SOURCE_DIR}/*.hxx"
)
list(FILTER EMBED_FIGLET_PUBLIC_HEADERS EXCLUDE REGEX ".*\\.tmpl$")

foreach(header IN LISTS EMBED_FIGLET_PUBLIC_HEADERS)
  set_source_files_properties("${header}" PROPERTIES HEADER_FILE_ONLY TRUE)
endforeach()

function(embed_figlet_set_target_output_dirs target_name)
  set_target_properties(
    ${target_name} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin"
  )
endfunction()

function(embed_figlet_configure_target target_name)
  target_compile_features(${target_name} PUBLIC cxx_std_20)
  target_compile_definitions(${target_name} PUBLIC _USE_MATH_DEFINES)
  target_include_directories(
    ${target_name}
    PUBLIC
      "$<BUILD_INTERFACE:${SOURCE_DIR}>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/lib3rd/include"
  )
  target_include_directories(
    ${target_name}
    SYSTEM PUBLIC
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib3rd/include>"
  )

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(${target_name} PRIVATE -Wall -Wextra)
  endif()

  set_target_properties(
    ${target_name} PROPERTIES
    VERSION ${PROJECT_VERSION}
    POSITION_INDEPENDENT_CODE ON
  )

  embed_figlet_set_target_output_dirs(${target_name})
endfunction()

function(embed_figlet_set_real_platform_name target_name base_name library_kind)
  if(library_kind STREQUAL "STATIC")
    set(output_name "${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}_static")
  else()
    set(output_name "${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}")
  endif()

  if(WIN32)
    set(output_name "lib${output_name}")
    set_target_properties(${target_name} PROPERTIES PREFIX "" IMPORT_PREFIX "")
  endif()

  set_target_properties(
    ${target_name} PROPERTIES
    OUTPUT_NAME         "${output_name}"
    ARCHIVE_OUTPUT_NAME "${output_name}"
    LIBRARY_OUTPUT_NAME "${output_name}"
    RUNTIME_OUTPUT_NAME "${output_name}"
  )
endfunction()

function(embed_figlet_add_generic_library_link target_name base_name library_kind)
  if(library_kind STREQUAL "STATIC")
    set(real_filename "${CMAKE_STATIC_LIBRARY_PREFIX}${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}_static${CMAKE_STATIC_LIBRARY_SUFFIX}")
    if(WIN32)
      set(real_filename "lib${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}_static${CMAKE_STATIC_LIBRARY_SUFFIX}")
      set(generic_filename "lib${base_name}${CMAKE_STATIC_LIBRARY_SUFFIX}")
    else()
      set(generic_filename "${CMAKE_STATIC_LIBRARY_PREFIX}${base_name}${CMAKE_STATIC_LIBRARY_SUFFIX}")
    endif()
  else()
    set(real_filename "${CMAKE_SHARED_LIBRARY_PREFIX}${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    if(WIN32)
      set(real_filename "lib${base_name}_${EMBED_FIGLET_PLATFORM_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}")
      set(generic_filename "lib${base_name}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    else()
      set(generic_filename "${CMAKE_SHARED_LIBRARY_PREFIX}${base_name}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()
  endif()

  # The suffixed file is the real artifact.  The generic name is only a
  # compatibility alias.  Remove stale artifacts produced by the previous
  # cmake_utils layout, where files could be placed directly in lib/ or in a
  # bogus lib/Users/... tree by a malformed install(CODE) path.
  set(legacy_root_real    "${CMAKE_CURRENT_SOURCE_DIR}/lib/${real_filename}")
  set(legacy_root_generic "${CMAKE_CURRENT_SOURCE_DIR}/lib/${generic_filename}")
  set(legacy_bad_users    "${CMAKE_CURRENT_SOURCE_DIR}/lib/Users")

  if(WIN32)
    add_custom_command(
      TARGET ${target_name} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E rm -f "${legacy_root_real}"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${legacy_root_generic}"
      COMMAND ${CMAKE_COMMAND} -E rm -rf "${legacy_bad_users}"
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              "$<TARGET_FILE:${target_name}>"
              "$<TARGET_FILE_DIR:${target_name}>/${generic_filename}"
      VERBATIM
    )
  else()
    add_custom_command(
      TARGET ${target_name} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E rm -f "${legacy_root_real}"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${legacy_root_generic}"
      COMMAND ${CMAKE_COMMAND} -E rm -rf "${legacy_bad_users}"
      COMMAND ${CMAKE_COMMAND} -E rm -f
              "$<TARGET_FILE_DIR:${target_name}>/${generic_filename}"
      COMMAND ${CMAKE_COMMAND} -E create_symlink
              "${real_filename}"
              "$<TARGET_FILE_DIR:${target_name}>/${generic_filename}"
      VERBATIM
    )
  endif()

  if(UTILS_INSTALL_LOCAL)
    # Keep install idempotent and do not create symlinks with absolute paths.
    # The target output directory is already ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
    # in the standard Rake workflow, so only cleanup of stale bad layouts is needed.
    install(CODE
      "file(REMOVE \"${legacy_root_real}\")\n"
      "file(REMOVE \"${legacy_root_generic}\")\n"
      "file(REMOVE_RECURSE \"${legacy_bad_users}\")\n"
    )
  endif()
endfunction()

set(EMBED_FIGLET_INSTALL_TARGETS)

add_library(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static STATIC ${EMBED_FIGLET_SOURCES} ${EMBED_FIGLET_PUBLIC_HEADERS})
add_library(${UTILS_NAMESPACE}::${PROJECT_NAME}_Static ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
embed_figlet_set_real_platform_name(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static ${PROJECT_NAME} STATIC)
embed_figlet_configure_target(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
embed_figlet_add_generic_library_link(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static ${PROJECT_NAME} STATIC)
list(APPEND EMBED_FIGLET_INSTALL_TARGETS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)

if(UTILS_BUILD_SHARED)
  add_library(${UTILS_NAMESPACE}_${PROJECT_NAME} SHARED ${EMBED_FIGLET_SOURCES} ${EMBED_FIGLET_PUBLIC_HEADERS})
  add_library(${UTILS_NAMESPACE}::${PROJECT_NAME} ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME})
  embed_figlet_set_real_platform_name(${UTILS_NAMESPACE}_${PROJECT_NAME} ${PROJECT_NAME} SHARED)
  embed_figlet_configure_target(${UTILS_NAMESPACE}_${PROJECT_NAME})
  embed_figlet_add_generic_library_link(${UTILS_NAMESPACE}_${PROJECT_NAME} ${PROJECT_NAME} SHARED)
  list(APPEND EMBED_FIGLET_INSTALL_TARGETS ${UTILS_NAMESPACE}_${PROJECT_NAME})
endif()

if(BUILD_EXECUTABLE OR UTILS_ENABLE_TESTS)
  enable_testing()

  set(EMBED_FIGLET_TEST_NAMES example test1)
  add_custom_target(${PROJECT_NAME}_all_tests ALL)
  add_custom_target(all_tests DEPENDS ${PROJECT_NAME}_all_tests)

  foreach(test_name IN LISTS EMBED_FIGLET_TEST_NAMES)
    set(test_source "${CMAKE_CURRENT_SOURCE_DIR}/src_tests/${test_name}.cc")
    if(EXISTS "${test_source}")
      add_executable(${test_name} "${test_source}")
      target_compile_features(${test_name} PRIVATE cxx_std_20)
      target_link_libraries(${test_name} PRIVATE ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static ${CMAKE_DL_LIBS})
      set_target_properties(
        ${test_name} PROPERTIES
        SUFFIX ".exe"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
      )
      add_test(
        NAME "${test_name}"
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/bin/${test_name}.exe"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      )
      add_dependencies(${PROJECT_NAME}_all_tests ${test_name})
    endif()
  endforeach()
endif()

if(UTILS_INSTALL_LOCAL)
  # Use absolute destinations for the local layout.  This avoids accidental
  # installation into ${CMAKE_CURRENT_SOURCE_DIR}/lib when an external
  # Rakefile or cache sets CMAKE_INSTALL_PREFIX to the source tree instead of
  # ${CMAKE_CURRENT_SOURCE_DIR}/lib.
  set(EMBED_FIGLET_LOCAL_INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
  set(EMBED_FIGLET_LOCAL_LIBDIR     "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib")
  set(EMBED_FIGLET_LOCAL_BINDIR     "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin")

  install(
    TARGETS ${EMBED_FIGLET_INSTALL_TARGETS}
    LIBRARY DESTINATION "${EMBED_FIGLET_LOCAL_LIBDIR}"
    ARCHIVE DESTINATION "${EMBED_FIGLET_LOCAL_LIBDIR}"
    RUNTIME DESTINATION "${EMBED_FIGLET_LOCAL_BINDIR}"
    INCLUDES DESTINATION "${EMBED_FIGLET_LOCAL_INCLUDEDIR}"
  )

  install(
    DIRECTORY "${SOURCE_DIR}/"
    DESTINATION "${EMBED_FIGLET_LOCAL_INCLUDEDIR}"
    FILES_MATCHING
      PATTERN "*.h"
      PATTERN "*.hh"
      PATTERN "*.hpp"
      PATTERN "*.hxx"
      PATTERN "*.tmpl" EXCLUDE
      PATTERN ".DS_Store" EXCLUDE
  )

  # Final cleanup after install(TARGETS).  This catches stale artifacts from
  # previous builds and also protects against misconfigured install prefixes.
  install(CODE
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_${EMBED_FIGLET_PLATFORM_SUFFIX}_static${CMAKE_STATIC_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_${EMBED_FIGLET_PLATFORM_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE_RECURSE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/Users\")\n"
  )
endif()

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "embedFiglet")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR}/;/\\\\.git/;/build.*/")
include(CPack)

message(STATUS "")
message(STATUS "${PROJECT_NAME} configuration summary:")
message(STATUS "  Version          : ${PROJECT_VERSION}")
message(STATUS "  Compiler         : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Platform suffix  : ${EMBED_FIGLET_PLATFORM_SUFFIX}")
message(STATUS "  Build shared     : ${UTILS_BUILD_SHARED}")
message(STATUS "  Build tests      : ${UTILS_ENABLE_TESTS}")
message(STATUS "  Install rules    : ${UTILS_INSTALL_LOCAL}")
message(STATUS "  Headers install  : ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "  Libraries install: ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "")
