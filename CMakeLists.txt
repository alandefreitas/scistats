#######################################################
### Scistats                                        ###
#######################################################
cmake_minimum_required(VERSION 3.14)
project(scistats VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

# CMake dependencies for installer
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Create variable with root path
set(SCISTATS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# To find or download packages
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
message("CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")
option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)
include(cmake/CPM.cmake)

# Check if this is a master project or a subdirectory of another project
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(MASTER_PROJECT ON)
else ()
    set(MASTER_PROJECT OFF)
endif ()

# Check if we are in debug mode
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(DEBUG_MODE ON)
    set(NOT_DEBUG_MODE OFF)
else ()
    set(DEBUG_MODE OFF)
    set(NOT_DEBUG_MODE ON)
endif ()

#######################################################
### Options                                         ###
#######################################################
# What to build
option(BUILD_EXAMPLES "Build examples" ${MASTER_PROJECT})
option(BUILD_TESTS "Build tests" ${MASTER_PROJECT})
option(BUILD_INSTALLER "Build installer target" ${MASTER_PROJECT})
option(BUILD_PACKAGE "Build package" ${MASTER_PROJECT})

# How to build
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_WITH_PEDANTIC_WARNINGS "Use pedantic warnings. This is useful for developers because many of these warnings will be in continuous integration anyway. This is ON by default in DEBUG mode." ${DEBUG_MODE})
option(BUILD_WITH_UTF8 "Accept utf-8 in MSVC by default." ON)

#######################################################
### Libraries                                       ###
#######################################################
add_subdirectory(source)

#######################################################
### Examples and tests                              ###
#######################################################
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()

#######################################################
### Installer                                       ###
#######################################################
if (BUILD_INSTALLER)
    # https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html
    # Set variable where the cmake config is
    set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/Scistats++)
    message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
    message("CMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}")

    # Create Scistats++ConfigVersion.cmake and install it
    write_basic_package_version_file(
            Scistats++ConfigVersion.cmake
            VERSION ${PACKAGE_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    # Create scistats++-config.cmake from scistats++-config.cmake.in
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/scistats++-config.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/scistats++-config.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scistats++)

    # Install the file scistats++-config.cmake
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/scistats++-config.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scistats++)

    # Install cmake file to find filesystem as a dependency
    if (NOT BUILD_SHARED_LIBS)
        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFilesystem.cmake
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scistats++)
    endif ()
endif ()