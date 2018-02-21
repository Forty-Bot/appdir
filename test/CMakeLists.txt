enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

function(add_custom_test TEST_NAME SOURCES)
	add_executable(${TEST_NAME} ${SOURCES})
	target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
	add_dependencies(check ${TEST_NAME})
endfunction()

add_custom_test(equiv equiv.c)
add_custom_test(print print.c)
