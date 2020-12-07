#######################################################
### External libraries                              ###
#######################################################
# Async++
CPMAddPackage(
        NAME Async++
        GITHUB_REPOSITORY Amanieu/asyncplusplus
        GIT_TAG v1.1
        VERSION 1.1
        DOWNLOAD_ONLY TRUE
        OPTIONS
        "BUILD_SHARED_LIBS OFF"
)
if (Async++_ADDED)
    SET(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as shared lib")
    add_subdirectory(${Async++_SOURCE_DIR} ${Async++_SOURCE_DIR}/../Async++-binaries EXCLUDE_FROM_ALL)
    if (NOT TARGET Async++)
        message(FATAL_ERROR Async++ directory included but Async++ target not found)
    endif ()
elseif (Async++_FOUND)
    if (NOT TARGET Async++)
        message(FATAL_ERROR Async++ found but Async++ target not found)
    endif ()
else ()
    message(FATAL_ERROR Cannot find or download Async++)
endif ()

if (UNIX)
    if (APPLE)
        set(COMPILE_OPTIONS_TO_IGNORE_ASYNCPP_WARNINGS
                -Wno-shadow-field-in-constructor
                -Wno-shadow
                -Wno-shadow-field
                -Wno-sign-conversion
                -Wno-implicit-float-conversion
                )
    else ()
        set(COMPILE_OPTIONS_TO_IGNORE_ASYNCPP_WARNINGS
                -Wno-error=sign-conversion
                )
    endif ()
endif ()

# Ranges
CPMAddPackage(
        NAME range-v3
        URL https://github.com/ericniebler/range-v3/archive/0.11.0.zip
        VERSION 0.11.0
        # the range-v3 CMakeLists screws with configuration options
        DOWNLOAD_ONLY True
)
if (range-v3_ADDED)
    add_library(range-v3 INTERFACE IMPORTED)
    target_include_directories(range-v3 INTERFACE "${range-v3_SOURCE_DIR}/include")
endif ()

# Threads
find_package(Threads REQUIRED)

#######################################################
### Library                                         ###
#######################################################
# Generate the main file with all headers for convenience only
file(GLOB_RECURSE ALL_HEADERS *.h)
set(ALL_HEADERS_FILE ${CMAKE_CURRENT_SOURCE_DIR}/scistats/scistats.h)
file(WRITE ${ALL_HEADERS_FILE} "// This file is generated automatically
// Do not modify
#ifndef SCISTATS_SCISTATS_ALL_HEADERS_H
#define SCISTATS_SCISTATS_ALL_HEADERS_H\n\n")
foreach (HEADER ${ALL_HEADERS})
    file(RELATIVE_PATH RELATIVE_HEADER ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER})
    file(APPEND ${ALL_HEADERS_FILE} "#include <${RELATIVE_HEADER}>\n")
endforeach ()
file(APPEND ${ALL_HEADERS_FILE} "\n#endif // SCISTATS_SCISTATS_ALL_HEADERS_H\n")

# Add interface target
add_library(scistats INTERFACE)
target_include_directories(scistats
        INTERFACE $<BUILD_INTERFACE:${SCISTATS_ROOT_DIR}/source>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(scistats INTERFACE Threads::Threads Async++ range-v3)
target_compile_options(scistats INTERFACE ${COMPILE_OPTIONS_TO_IGNORE_ASYNCPP_WARNINGS})

# https://cmake.org/cmake/help/v3.14/manual/cmake-compile-features.7.html#requiring-language-standards
target_compile_features(scistats INTERFACE cxx_std_20)

# Hacks to support MSVC
if (MSVC)
    # World maps require this option because there is so much in the file
    target_compile_options(scistats INTERFACE /bigobj)
    target_compile_options(scistats INTERFACE /wd4305)
    # Fix compile error caused by utf8 character in line_spec.cpp
    target_compile_options(scistats INTERFACE /utf-8)
    # Allow exceptions
    target_compile_options(scistats INTERFACE /EHsc)
endif ()

# Another hack to check for min in Windows.h
# http://www.suodenjoki.dk/us/archive/2010/min-max.htm
include(CheckSymbolExists)
check_symbol_exists(min "Windows.h" HAVE_WINDOWS_MINMAX)
if (HAVE_WINDOWS_MINMAX)
    target_compile_definitions(scistats INTERFACE NOMINMAX)
endif ()

# Use pedantic warnings especially in debug mode
if (BUILD_WITH_PEDANTIC_WARNINGS)
    if (MSVC)
        target_compile_options(scistats INTERFACE /W4 /WX)
    else ()
        target_compile_options(scistats INTERFACE -Wall -Wextra -pedantic -Werror)
        # Allow the warnings related to the bundled CImg
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
            target_compile_options(scistats INTERFACE -Wno-null-pointer-arithmetic -Wno-char-subscripts)
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(scistats INTERFACE -Wno-error=class-memaccess -Wno-class-memaccess)
        else ()
            message(ERROR "Cannot disable the relevant warnings for ${CMAKE_CXX_COMPILER_ID}")
        endif ()
    endif ()
endif ()

#######################################################
### Installer                                       ###
#######################################################
if (BUILD_INSTALLER)
    # Install targets
    install(TARGETS scistats
            EXPORT Scistats++Targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            )

    # Install headers
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN "*.h"
            )

    # Install cmake script
    install(EXPORT Scistats++Targets
            FILE Scistats++Targets.cmake
            NAMESPACE Scistats++::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scistats++
            )
endif ()