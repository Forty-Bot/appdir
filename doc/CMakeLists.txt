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

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
	set(DOCSTAMP "${CMAKE_CURRENT_BINARY_DIR}/doxygen.stamp")
	set(DOCSRC "${CMAKE_SOURCE_DIR}/include/appdir.h")
	configure_file(doxyfile.in ${DOXYFILE} @ONLY)
	add_custom_command(OUTPUT ${DOCSTAMP}
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		COMMAND ${CMAKE_COMMAND} -E touch ${DOCSTAMP}
		DEPENDS ${DOXYFILE} ${DOCSRC}
		COMMENT "Generating Documentation"
		VERBATIM)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_custom_target(doc ALL DEPENDS ${DOCSTAMP})
	else()
		add_custom_target(doc DEPENDS ${DOCSTAMP})
	endif()
endif()
