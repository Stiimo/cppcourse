project(w5_t2)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} main.cpp transliterator.cpp transliterator.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/table.tsv ${CMAKE_BINARY_DIR}/bin)
