file(GLOB WEEK_DIRS "task*")
foreach (WEEK_DIR ${WEEK_DIRS})
    add_subdirectory(${WEEK_DIR})
endforeach ()
