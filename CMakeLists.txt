add_library(s_cobs
    srs/cobs.c
)
target_include_directories(s_cobs
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)