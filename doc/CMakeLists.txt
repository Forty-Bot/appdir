find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
	set(DOCSTAMP "${CMAKE_CURRENT_BINARY_DIR}/doxygenstamp")
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
