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

enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

function(add_custom_test TEST_NAME SOURCES)
	add_executable(${TEST_NAME} ${SOURCES})
	target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
	set_property(TARGET ${TEST_NAME}
		PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	add_dependencies(check ${TEST_NAME})
endfunction()

add_custom_test(equiv equiv.c)
add_custom_test(fallbacks fallbacks.c)
add_custom_test(invalids invalids.c)
add_custom_test(print print.c)
