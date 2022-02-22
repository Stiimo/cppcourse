project(w2_t2)

add_executable(${PROJECT_NAME} main.cpp timer.h)
target_link_libraries(${PROJECT_NAME} PRIVATE progress_bar)
