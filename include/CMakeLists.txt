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

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

if(CREATE_ARCHIVE)
	set(DEST ".")
else()
	set(DEST ${CMAKE_INSTALL_INCLUDEDIR})
endif()
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/appdir.h"
	"${CMAKE_CURRENT_BINARY_DIR}/appdir_export.h"
	DESTINATION ${DEST})
