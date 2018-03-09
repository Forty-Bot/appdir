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

set(SOURCES appdir.c)
if(UNIX)
	if(APPLE)
		list(APPEND SOURCES dummy.c)
	else()
		list(APPEND SOURCES posix.c)
	endif()
elseif(WIN32)
	list(APPEND SOURCES windows.c)
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if(UNIX AND NOT APPLE)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(XDG_BASEDIR REQUIRED libxdg-basedir)
	target_link_libraries(${PROJECT_NAME} ${XDG_BASEDIR_LIBRARIES})
endif()

if(CREATE_ARCHIVE)
	set(DEST ".")
else()
	set(DEST ${CMAKE_INSTALL_LIBDIR})
endif()
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${DEST})
