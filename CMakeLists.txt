add_library(s_cobs
    cobs.c
)
target_include_directories(s_cobs
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)