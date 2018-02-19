cmake_minimum_required(VERSION 3.0)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
		"In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

set(PROJECT_NAME appdir)
project(${PROJECT_NAME} VERSION 0.0.1.0)

find_package(PkgConfig REQUIRED)
if(UNIX AND NOT APPLE)
	pkg_check_modules(XDG_BASEDIR REQUIRED libxdg-basedir)
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
