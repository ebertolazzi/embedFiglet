############################################################################
#                                                                          #
#  embedFiglet -- standalone CMake build, no cmake_utils submodule.         #
#                                                                          #
#  This file intentionally keeps all build rules self-contained. It defines #
#  the library targets, the optional shared-library variant, compatibility   #
#  target names used by older build scripts, local install directories,      #
#  optional test/example executables, packaging metadata, and the legacy     #
#  generic library-name aliases expected by the existing Rake/CMake flow.    #
#                                                                          #
############################################################################

# The minimum CMake version is kept at 3.16 because the project only uses
# features available at that level, while still allowing newer CMake releases
# to opt into more deterministic policy behavior below.
cmake_minimum_required(VERSION 3.16)

# --------------------------------------------------------------------------
# CMake policy selection
# --------------------------------------------------------------------------
# Policies are guarded because users may configure the project with several
# different CMake versions. Setting newer policies only when they exist avoids
# warnings on recent CMake while preserving compatibility with older CMake.
#
# CMP0177 affects install path normalization in recent CMake versions. NEW
# behavior gives more predictable install destinations.
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.31)
  cmake_policy(SET CMP0177 NEW)
endif()

# CMP0135 controls timestamp handling for archives downloaded by CMake helper
# commands. NEW behavior avoids stale rebuild decisions when archive contents
# are extracted with preserved timestamps.
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# --------------------------------------------------------------------------
# Project version discovery
# --------------------------------------------------------------------------
# The public project version is read from the latest Git tag when possible.
# This keeps packages, installed targets, and generated archive metadata tied
# to the repository tag without requiring the version to be duplicated here.
#
# If Git is unavailable, or the source tree is not a Git checkout, the project
# falls back to a stable default version so that configuration still works from
# source archives or vendored copies.
find_package(Git QUIET)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE EMBED_FIGLET_PROJECT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  # Tags are often written as v1.2.3. CMake project(VERSION) expects the plain
  # numeric form, so strip one leading 'v' if present.
  if(EMBED_FIGLET_PROJECT_VERSION MATCHES "^v")
    string(SUBSTRING "${EMBED_FIGLET_PROJECT_VERSION}" 1 -1 EMBED_FIGLET_PROJECT_VERSION)
  endif()
endif()
if(NOT EMBED_FIGLET_PROJECT_VERSION)
  set(EMBED_FIGLET_PROJECT_VERSION "1.0.0")
endif()

# --------------------------------------------------------------------------
# Apple FAT/universal build setup
# --------------------------------------------------------------------------
# On Apple platforms a single library can contain slices for several CPU
# architectures, for example arm64 and x86_64.  This is controlled by
# CMAKE_OSX_ARCHITECTURES.
#
# The variable must be set before project(), otherwise CMake may initialize
# compilers and targets before the requested architectures are known.
#
# Default behavior:
#   - ON  on Apple hosts or Apple cross-compilation targets.
#   - OFF on Linux/Windows and other platforms, where there is no equivalent
#     single-file universal library format.
#
# User overrides:
#   -DUTILS_BUILD_FAT=OFF
#   -DUTILS_FAT_ARCHITECTURES=arm64
#   -DCMAKE_OSX_ARCHITECTURES=arm64\;x86_64
set(UTILS_BUILD_FAT_DEFAULT OFF)
if(CMAKE_HOST_APPLE OR CMAKE_SYSTEM_NAME MATCHES "Darwin|iOS|tvOS|watchOS|visionOS")
  set(UTILS_BUILD_FAT_DEFAULT ON)
endif()
option(UTILS_BUILD_FAT "Build Apple universal/fat binaries when supported" ${UTILS_BUILD_FAT_DEFAULT})
set(UTILS_FAT_ARCHITECTURES "arm64;x86_64" CACHE STRING "Apple architectures to build when UTILS_BUILD_FAT is ON")

if(UTILS_BUILD_FAT AND NOT CMAKE_OSX_ARCHITECTURES)
  set(
    CMAKE_OSX_ARCHITECTURES
    "${UTILS_FAT_ARCHITECTURES}"
    CACHE STRING "Build architectures for Apple platforms"
    FORCE
  )
endif()

# --------------------------------------------------------------------------
# Project declaration
# --------------------------------------------------------------------------
# project() enables the requested languages, detects compilers, initializes
# platform variables, and records the version metadata used later by target
# properties and CPack. Keep architecture-related Apple settings above this
# call so CMake configures the compiler for the requested slices from the
# beginning of the configure step.
project(
  embedFiglet
  VERSION ${EMBED_FIGLET_PROJECT_VERSION}
  HOMEPAGE_URL "https://ebertolazzi.github.io/embedFiglet/"
  LANGUAGES CXX
)

# --------------------------------------------------------------------------
# Standard CMake modules
# --------------------------------------------------------------------------
# GNUInstallDirs provides portable install-directory variables such as
# CMAKE_INSTALL_INCLUDEDIR, CMAKE_INSTALL_LIBDIR, and CMAKE_INSTALL_BINDIR.
# CTest defines BUILD_TESTING and the test-registration commands used below.
include(GNUInstallDirs)
include(CTest)

# --------------------------------------------------------------------------
# Public build options and compatibility switches
# --------------------------------------------------------------------------
# These cache options are the user-facing build contract. They intentionally
# mirror names used by earlier cmake_utils-based builds so existing scripts can
# continue to drive this standalone CMakeLists.txt without changes.
option(UTILS_GIT_VERSION "Get version from Git command" ON)
option(UTILS_ENABLE_TESTS "Enable compilation of testing targets" OFF)
option(UTILS_BUILD_SHARED "Enable shared library compilation" OFF)
option(UTILS_INSTALL_LOCAL "Enable installation into local lib directory" ON)
option(UTILS_TWEAK_VERSION_IS_TIMESTAMP "Set tweak version to timestamp" OFF)
option(BUILD_SHARED "Compatibility alias for UTILS_BUILD_SHARED" ${UTILS_BUILD_SHARED})
option(BUILD_EXECUTABLE "Compatibility alias for building tests/examples" OFF)

# BUILD_SHARED is retained as a legacy alias. If an older script enables it,
# normalize the project to the canonical UTILS_BUILD_SHARED option used by the
# rest of this file.
if(BUILD_SHARED AND NOT UTILS_BUILD_SHARED)
  set(UTILS_BUILD_SHARED ON CACHE BOOL "Enable shared library compilation" FORCE)
endif()

# Namespace used for compatibility imported/alias targets, e.g.
# utils::embedFiglet_Static. Keeping it configurable lets downstream projects
# preserve existing target naming conventions.
set(UTILS_NAMESPACE "utils" CACHE STRING "Namespace prefix used for compatibility targets")

# --------------------------------------------------------------------------
# Local install layout
# --------------------------------------------------------------------------
# When this repository is configured as the top-level project, install into the
# repository-local lib/ tree by default. This matches the historical layout:
#   lib/include  public headers
#   lib/lib      static/shared libraries
#   lib/bin      runtime binaries
#
# If a parent project includes this project as a subdirectory, it can still set
# its own CMAKE_INSTALL_PREFIX and install directories before configuration.
if(PROJECT_IS_TOP_LEVEL AND (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local"))
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/lib" CACHE PATH "Install prefix" FORCE)
endif()
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Install include directory" FORCE)
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Install library directory" FORCE)
set(CMAKE_INSTALL_BINDIR "bin" CACHE PATH "Install binary directory" FORCE)

# Create the expected output directories early. This keeps generators, custom
# commands, Rake wrappers, and install rules from failing because the legacy
# local layout has not been materialized yet.
file(MAKE_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin"
  "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# --------------------------------------------------------------------------
# Default configuration type
# --------------------------------------------------------------------------
# Single-config generators such as Unix Makefiles and Ninja use
# CMAKE_BUILD_TYPE. Multi-config generators such as Xcode and Visual Studio use
# CMAKE_CONFIGURATION_TYPES instead and ignore this variable.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# --------------------------------------------------------------------------
# C++ language mode and compile database
# --------------------------------------------------------------------------
# The library requires C++20. Extensions are disabled so consumers get a
# portable language mode instead of compiler-specific dialects such as gnu++20.
# compile_commands.json is exported to support IDEs, clangd, clang-tidy, and
# other source-analysis tools.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# --------------------------------------------------------------------------
# Platform suffix used in real library filenames
# --------------------------------------------------------------------------
# The actual produced library files include a platform suffix, e.g.
#   libembedFiglet_osx_static.a
#   libembedFiglet_linux_static.a
#   libembedFiglet_win64_static.lib
#
# A generic compatibility alias is created later. This suffix only describes
# the operating system/toolchain family; on Apple it does not encode every CPU
# slice. Universal/FAT architectures are controlled separately by
# CMAKE_OSX_ARCHITECTURES above.
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

# Do not reset CMAKE_OSX_ARCHITECTURES here. Older versions of this file used
# uname -m after project(), which forced the build to the host architecture and
# prevented arm64/x86_64 universal binaries. The FAT/universal block above is
# the single source of truth for Apple architecture selection.

# --------------------------------------------------------------------------
# Optional user customization hook
# --------------------------------------------------------------------------
# A sibling CMakeLists-customize.txt can inject site-specific settings without
# editing this file. This is useful for local compiler flags, toolchain tweaks,
# custom paths, or experimental options maintained outside the canonical build.
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/../CMakeLists-customize.txt")
  include("${CMAKE_CURRENT_LIST_DIR}/../CMakeLists-customize.txt")
endif()

# --------------------------------------------------------------------------
# Compiler warning adjustments
# --------------------------------------------------------------------------
# These warnings are intentionally disabled only for Clang-family compilers.
# They are generally noisy for this codebase or for packaged-system include
# layouts, while -Wall/-Wextra are still added per target below.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
  add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-poison-system-directories>"
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-switch-default>"
    "$<$<COMPILE_LANGUAGE:CXX>:-Wno-exit-time-destructors>"
  )
endif()

# --------------------------------------------------------------------------
# Source tree discovery
# --------------------------------------------------------------------------
# SOURCE_DIR is the root of the library implementation and public headers.
# Keeping it in one variable avoids hard-coding the same path throughout target
# definitions, install rules, and include directories.
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# All .cc files under src/ are compiled into the library. CONFIGURE_DEPENDS
# asks CMake to re-run configuration when matching files are added or removed.
file(GLOB_RECURSE EMBED_FIGLET_SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cc")

# hsl_fake.cc is deliberately excluded. It is present in the source tree for
# compatibility/testing purposes but must not be part of the production library.
list(FILTER EMBED_FIGLET_SOURCES EXCLUDE REGEX ".*hsl_fake\\.cc$")

# Collect public headers so IDE generators display them in the target and so
# install rules can mirror the source-tree header layout. Template files are
# intentionally excluded from the public install surface.
file(GLOB_RECURSE EMBED_FIGLET_PUBLIC_HEADERS CONFIGURE_DEPENDS
  "${SOURCE_DIR}/*.h"
  "${SOURCE_DIR}/*.hh"
  "${SOURCE_DIR}/*.hpp"
  "${SOURCE_DIR}/*.hxx"
)
list(FILTER EMBED_FIGLET_PUBLIC_HEADERS EXCLUDE REGEX ".*\\.tmpl$")

# Mark headers as non-compilable source entries. This makes them visible in IDE
# project views without causing any generator to try compiling them.
foreach(header IN LISTS EMBED_FIGLET_PUBLIC_HEADERS)
  set_source_files_properties("${header}" PROPERTIES HEADER_FILE_ONLY TRUE)
endforeach()

# --------------------------------------------------------------------------
# Helper: common target output directories
# --------------------------------------------------------------------------
# Libraries and runtime files are written directly into the historical local
# layout. This avoids requiring an install step for the standard development
# workflow and keeps compatibility with scripts that expect lib/lib and lib/bin.
function(embed_figlet_set_target_output_dirs target_name)
  set_target_properties(
    ${target_name} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin"
  )
endfunction()

# --------------------------------------------------------------------------
# Helper: common target configuration
# --------------------------------------------------------------------------
# This function centralizes requirements shared by the static and shared
# library variants: C++ standard, compile definitions, public/private include
# directories, warnings, version metadata, position-independent code, and output
# locations. Keeping these properties in one place prevents the static and
# shared targets from drifting apart.
function(embed_figlet_configure_target target_name)
  # Propagate C++20 as part of the public usage requirements, because consumers
  # including this target may need the same language level for headers.
  target_compile_features(${target_name} PUBLIC cxx_std_20)

  # _USE_MATH_DEFINES enables constants such as M_PI on MSVC-compatible C/C++
  # runtimes. It is harmless elsewhere and keeps cross-platform source code
  # simpler.
  target_compile_definitions(${target_name} PUBLIC _USE_MATH_DEFINES)

  # Public include directories are exposed to consumers. BUILD_INTERFACE is used
  # while building from the source tree; INSTALL_INTERFACE is used after the
  # target is installed and imported from a package layout.
  target_include_directories(
    ${target_name}
    PUBLIC
      "$<BUILD_INTERFACE:${SOURCE_DIR}>"
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/lib3rd/include"
  )

  # Third-party headers are marked SYSTEM to reduce warnings originating from
  # bundled dependencies when compilers use -Wall/-Wextra.
  target_include_directories(
    ${target_name}
    SYSTEM PUBLIC
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib3rd/include>"
  )

  # Apply useful warnings for GCC/Clang-family compilers. MSVC is intentionally
  # not handled here because warning-level semantics differ substantially.
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(${target_name} PRIVATE -Wall -Wextra)
  endif()

  # VERSION is used by shared-library metadata on platforms that support it.
  # POSITION_INDEPENDENT_CODE keeps the static library usable from shared
  # libraries and is required for shared-library builds on many platforms.
  set_target_properties(
    ${target_name} PROPERTIES
    VERSION ${PROJECT_VERSION}
    POSITION_INDEPENDENT_CODE ON
  )

  embed_figlet_set_target_output_dirs(${target_name})
endfunction()

# --------------------------------------------------------------------------
# Helper: assign the real platform-specific library filename
# --------------------------------------------------------------------------
# The real artifact name carries the platform suffix and, for static libraries,
# the _static suffix. A separate generic name is created later as a compatibility
# alias. On Windows, historical naming expects a lib prefix even though CMake's
# native Windows library names do not always add one by default.
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

# --------------------------------------------------------------------------
# Helper: create the generic compatibility library name
# --------------------------------------------------------------------------
# The platform-suffixed library is the authoritative artifact. The generic name
# exists only for older build scripts and consumers that link libembedFiglet.a
# or libembedFiglet.dylib directly.
#
# On Unix-like systems the generic file is a relative symlink to the real file.
# On Windows a copy is used because symlink behavior depends on privileges and
# developer-mode settings. The function also removes stale files produced by
# previous cmake_utils layouts, including broken lib/Users/... trees.
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

  # The suffixed file is the real artifact. The generic name is only a
  # compatibility alias. Remove stale artifacts produced by the previous
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

# --------------------------------------------------------------------------
# Library targets
# --------------------------------------------------------------------------
# This list accumulates targets that should be installed when local install
# rules are enabled. The static library is always built; the shared library is
# added only when UTILS_BUILD_SHARED is ON.
set(EMBED_FIGLET_INSTALL_TARGETS)

# Static library target. The physical target name preserves the historical
# namespace prefix while ALIAS targets provide both the utils:: compatibility
# name and a project-style embedFiglet::embedFiglet name for consumers.
add_library(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static STATIC ${EMBED_FIGLET_SOURCES} ${EMBED_FIGLET_PUBLIC_HEADERS})
add_library(${UTILS_NAMESPACE}::${PROJECT_NAME}_Static ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
embed_figlet_set_real_platform_name(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static ${PROJECT_NAME} STATIC)
embed_figlet_configure_target(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)
embed_figlet_add_generic_library_link(${UTILS_NAMESPACE}_${PROJECT_NAME}_Static ${PROJECT_NAME} STATIC)
list(APPEND EMBED_FIGLET_INSTALL_TARGETS ${UTILS_NAMESPACE}_${PROJECT_NAME}_Static)

# Optional shared library target. It uses the same sources and configuration as
# the static target but has its own real platform-specific output name and its
# own generic compatibility alias.
if(UTILS_BUILD_SHARED)
  add_library(${UTILS_NAMESPACE}_${PROJECT_NAME} SHARED ${EMBED_FIGLET_SOURCES} ${EMBED_FIGLET_PUBLIC_HEADERS})
  add_library(${UTILS_NAMESPACE}::${PROJECT_NAME} ALIAS ${UTILS_NAMESPACE}_${PROJECT_NAME})
  embed_figlet_set_real_platform_name(${UTILS_NAMESPACE}_${PROJECT_NAME} ${PROJECT_NAME} SHARED)
  embed_figlet_configure_target(${UTILS_NAMESPACE}_${PROJECT_NAME})
  embed_figlet_add_generic_library_link(${UTILS_NAMESPACE}_${PROJECT_NAME} ${PROJECT_NAME} SHARED)
  list(APPEND EMBED_FIGLET_INSTALL_TARGETS ${UTILS_NAMESPACE}_${PROJECT_NAME})
endif()

# --------------------------------------------------------------------------
# Optional tests / example executables
# --------------------------------------------------------------------------
# Tests are controlled by either the modern UTILS_ENABLE_TESTS option or the
# legacy BUILD_EXECUTABLE switch. The source files are optional: each executable
# is created only if its corresponding src_tests/<name>.cc exists.
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

# --------------------------------------------------------------------------
# Local install rules
# --------------------------------------------------------------------------
# The install step mirrors the build-tree layout into the repository-local
# lib/ tree. Absolute destinations are used deliberately to avoid accidental
# installation into a wrong prefix when external tooling modifies
# CMAKE_INSTALL_PREFIX.
if(UTILS_INSTALL_LOCAL)
  # Use absolute destinations for the local layout. This avoids accidental
  # installation into ${CMAKE_CURRENT_SOURCE_DIR}/lib when an external
  # Rakefile or cache sets CMAKE_INSTALL_PREFIX to the source tree instead of
  # ${CMAKE_CURRENT_SOURCE_DIR}/lib.
  set(EMBED_FIGLET_LOCAL_INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
  set(EMBED_FIGLET_LOCAL_LIBDIR     "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib")
  set(EMBED_FIGLET_LOCAL_BINDIR     "${CMAKE_CURRENT_SOURCE_DIR}/lib/bin")

  # Install all built library targets into the local layout. INCLUDES records
  # the include destination as usage metadata for installed targets.
  install(
    TARGETS ${EMBED_FIGLET_INSTALL_TARGETS}
    LIBRARY DESTINATION "${EMBED_FIGLET_LOCAL_LIBDIR}"
    ARCHIVE DESTINATION "${EMBED_FIGLET_LOCAL_LIBDIR}"
    RUNTIME DESTINATION "${EMBED_FIGLET_LOCAL_BINDIR}"
    INCLUDES DESTINATION "${EMBED_FIGLET_LOCAL_INCLUDEDIR}"
  )

  # Install public headers while preserving their relative paths under src/.
  # Template files and macOS Finder metadata are excluded from the installed
  # public interface.
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

  # Final cleanup after install(TARGETS). This catches stale artifacts from
  # previous builds and also protects against misconfigured install prefixes.
  install(CODE
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_${EMBED_FIGLET_PLATFORM_SUFFIX}_static${CMAKE_STATIC_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_${EMBED_FIGLET_PLATFORM_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}\")\n"
    "file(REMOVE_RECURSE \"${CMAKE_CURRENT_SOURCE_DIR}/lib/Users\")\n"
  )
endif()

# --------------------------------------------------------------------------
# Packaging metadata
# --------------------------------------------------------------------------
# CPack can generate binary and source archives from the configured build tree.
# The ignore list excludes the active build directory, Git metadata, and other
# build-* directories so source packages contain only source-relevant content.
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "embedFiglet")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR}/;/\\\\.git/;/build.*/")
include(CPack)

# --------------------------------------------------------------------------
# Configuration summary
# --------------------------------------------------------------------------
# Print the effective build choices at the end of configuration. This is useful
# in CI logs and when diagnosing user reports, because it records the detected
# compiler, platform suffix, optional targets, install behavior, and Apple
# universal-build architecture selection.
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
message(STATUS "  Build FAT        : ${UTILS_BUILD_FAT}")
message(STATUS "  Apple archs      : ${CMAKE_OSX_ARCHITECTURES}")
message(STATUS "")
