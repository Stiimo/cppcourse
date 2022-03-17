project(w6_t1)

add_executable(${PROJECT_NAME} main.cpp preprocessor.cpp preprocessor.h)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/test.txt ${CMAKE_BINARY_DIR}/bin)