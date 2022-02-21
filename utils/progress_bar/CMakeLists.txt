project(progress_bar)

add_library(${PROJECT_NAME} SHARED progressbar.cpp include/progress_bar/progressbar.h)
target_include_directories(${PROJECT_NAME} PUBLIC include)