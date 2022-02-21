cmake_minimum_required(VERSION 3.5)
project(cppcourse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(utils)
file(GLOB WEEK_DIRS "week*")
foreach (WEEK_DIR ${WEEK_DIRS})
    add_subdirectory(${WEEK_DIR})
endforeach ()
