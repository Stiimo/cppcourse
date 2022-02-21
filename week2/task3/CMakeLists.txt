project(w2_t3)

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} vector_to_multiarray_raw.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
