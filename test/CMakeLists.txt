enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

add_executable(equiv equiv.c)
target_link_libraries(equiv ${PROJECT_NAME})
add_test(NAME equiv COMMAND equiv)
add_dependencies(check equiv)
