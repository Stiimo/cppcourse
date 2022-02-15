cmake_minimum_required(VERSION 3.5)

project(task3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_executable(task3 vector_to_multiarray_raw.cpp)
target_link_libraries(task3 PRIVATE Boost::boost)
