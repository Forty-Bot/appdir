# Copyright (C) 2018 Sean Anderson
#
# This file is part of appdir.
#
# appdir is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# appdir is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with appdir. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.3)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
		"In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

set(PROJECT_NAME appdir)
project(${PROJECT_NAME}
	DESCRIPTION "C library for finding platform-specific dirs")

# Try to get the version from git
# nicked from https://wiki.archlinux.org/index.php/VCS_package_guidelines#Git
find_package(Git)
if(GIT_FOUND)
	# First try to base the version off a tag
	execute_process(COMMAND ${GIT_EXECUTABLE}
		"describe" "--long" "--tags"
		RESULT_VARIABLE GIT_RES
		OUTPUT_VARIABLE GIT_OUT)
	# Note that a successful result (0) is FALSE
	if(NOT GIT_RES)
		string(REGEX REPLACE "([^-]*-)g" "r\\1" TMP ${GIT_OUT})
		string(REPLACE "-" "." TMP ${TMP})
		string(REPLACE "\n" "" PROJECT_VERSION ${TMP})
	else()
		# if that doesn't work, we can always make something based
		# on the hash and revision count
		execute_process(COMMAND ${GIT_EXECUTABLE}
			"rev-list" "--count" "HEAD"
			RESULT_VARIABLE REV_COUNT_RES
			OUTPUT_VARIABLE REV_COUNT)
		execute_process(COMMAND ${GIT_EXECUTABLE}
			"rev-parse" "--short" "HEAD"
			RESULT_VARIABLE REV_SHORT_RES
			OUTPUT_VARIABLE REV_SHORT)
		if((NOT REV_COUNT_RES) AND (NOT REV_SHORT_RES))
			string(REPLACE "\n" "" PROJECT_VERSION
				"0.0.r${REV_COUNT}.${REV_SHORT}")
		endif()
	endif()
endif()

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

if(NOT PROJECT_VERSION)
	set(PROJECT_VERSION "0.0.1.0")
endif()

message(STATUS "Configuring ${PROJECT_NAME}-${PROJECT_VERSION}")

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}/include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set the default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_C_FLAGS AND NOT CMAKE_CXX_FLAGS)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Add -Wall or equivalent
if(MSVC)
	# Force to always compile with W4
	if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
	endif()
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
endif()

# Set the standard to C89
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)

# Set visibility settings (needed for export header)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

option(BUILD_TESTS "Build tests" OFF)
# Do this in the top-level file so we can run ctest from the root build dir
enable_testing()

if(UNIX)
	set(_CREATE_ARCHIVE FALSE)
else()
	set(_CREATE_ARCHIVE TRUE)
endif()
option(CREATE_ARCHIVE
	"Install files in an archive-style layout. This is meant to be used when creating an archive with CPack"
	${_CREATE_ARCHIVE})

# Initialize install dir helpers
include(GNUInstallDirs)

if(CREATE_ARCHIVE)
	set(DEST ".")
else()
	set(DEST ${CMAKE_INSTALL_DOCDIR})
endif()
install(FILES "${CMAKE_SOURCE_DIR}/README.md"
	"${CMAKE_SOURCE_DIR}/COPYING.LESSER"
	DESTINATION ${DEST})

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
if(BUILD_TESTS)
	add_subdirectory("${CMAKE_SOURCE_DIR}/test")
else()
	add_subdirectory("${CMAKE_SOURCE_DIR}/test" EXCLUDE_FROM_ALL)
endif()
add_subdirectory("${CMAKE_SOURCE_DIR}/doc")
add_subdirectory("${CMAKE_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_SOURCE_DIR}/cmake")

set(CPACK_PACKAGE_CONTACT "seanga2@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/copyright")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

set(CPACK_MONOLITHIC_INSTALL TRUE)
set(CPACK_STRIP_FILES TRUE)

include(CPack)
