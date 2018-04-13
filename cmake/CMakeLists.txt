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

if(CREATE_ARCHIVE)
	set(DEST "cmake")
else()
	set(DEST "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file("appdir-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/appdir-config.cmake"
	INSTALL_DESTINATION ${DEST})
# We need exact version since we haven't reached 1.0 yet
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/appdir-config-version.cmake"
	COMPATIBILITY ExactVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/appdir-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/appdir-config-version.cmake"
	DESTINATION ${DEST})

install(EXPORT appdir-targets DESTINATION ${DEST})
