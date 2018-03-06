# Copyright (C) 2018 Sean Anderson
#
# This file is part of c-appdir.
#
# c-appdir is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# c-appdir is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with c-appdir. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
		"In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

set(PROJECT_NAME appdir)
project(${PROJECT_NAME} VERSION 0.0.1.0)

if(UNIX AND NOT APPLE)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(XDG_BASEDIR REQUIRED libxdg-basedir)
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")

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

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/test" EXCLUDE_FROM_ALL)
add_subdirectory("${CMAKE_SOURCE_DIR}/doc")
