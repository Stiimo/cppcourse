cmake_minimum_required(VERSION 3.5)
project(cppcourse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/static_lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

add_subdirectory(thirdparty)
add_subdirectory(utils)
file(GLOB WEEK_DIRS "week*")
foreach (WEEK_DIR ${WEEK_DIRS})
    add_subdirectory(${WEEK_DIR})
endforeach ()
