project(w9_t)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp types.h
        ShmClient.cpp ShmClient.h
        Reader.cpp Reader.h
        InterruptableThread.cpp InterruptableThread.h
        Writer.cpp Writer.h
        StopToken.cpp StopToken.h
        Console.cpp Console.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Threads::Threads rt)

target_compile_definitions(${PROJECT_NAME} PRIVATE BOOST_DATE_TIME_NO_LIB)