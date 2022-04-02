project(w7_t3)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
