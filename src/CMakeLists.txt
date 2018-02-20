set(SOURCES appdir.c)
if(UNIX)
	if(APPLE)
		list(APPEND SOURCES dummy.c)
	else()
		list(APPEND SOURCES linux.c)
	endif()
elseif(WIN32)
	list(APPEND SOURCES dummy.c)
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if(XDG_BASEDIR_FOUND)
	target_link_libraries(${PROJECT_NAME} ${XDG_BASEDIR_LIBRARIES})
endif()

# Set the standard to C89
set(C_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_EXTENSIONS OFF)
