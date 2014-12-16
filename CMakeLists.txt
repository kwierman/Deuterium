# Kevin Wierman <kwierman@email.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Deuterium)
set(Deuterium_MAJOR_VERSION 0)
set(Deuterium_MINOR_VERSION 1)
set(Deuterium_PATCH_VERSION 0)
set(Deuterium_VERSION
  ${Deuterium_MAJOR_VERSION}.${Deuterium_MINOR_VERSION}.${Deuterium_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
#----------------------------------------------------------------------------
find_package(Protium REQUIRED)
if (PROTIUM_FOUND)
  include_directories(${PROTIUM_INCLUDE_DIRS})
endif (PROTIUM_FOUND)
#----------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS ${PROJECT_NAME} " requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()
#----------------------------------------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()
#----------------------------------------------------------------------------
#export(package Deuterium)
#file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
#set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
#configure_file(DeuteriumConfig.cmake.in "${PROJECT_BINARY_DIR}/DeuteriumConfig.cmake" @ONLY)
#set(CONF_INCLUDE_DIRS "\${Deuterium_CMAKE_DIR}/${REL_INCLUDE_DIR}")
#configure_file(DeuteriumConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DeuteriumConfig.cmake" @ONLY)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/..)
add_subdirectory(Options)
add_subdirectory(FileSystem)

#add_subdirectory(DataFormat)
add_subdirectory(Networking)
add_subdirectory(Applications)
#----------------------------------------------------------------------------
#Add in Documentation
add_subdirectory(Documentation)
#----------------------------------------------------------------------------
# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
#----------------------------------------------------------------------------

#Export everything just made                                               
install(EXPORT DeuteriumConfig DESTINATION lib/Deuterium)