cmake_minimum_required(VERSION 2.8)

project(src)

set(EXECUTABLE_OUTPUT_PATH ../bin)

ADD_DEFINITIONS(-std=c++11 -g -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wredundant-decls -Winline -Wno-long-long -Wuninitialized -Wconversion)
SET(CMAKE_EXE_LINKER_FLAGS "-g")

include_directories(.)

file(
        GLOB_RECURSE
        source_files
        ./*
)

add_executable(src ${source_files})

target_link_libraries(
    src
    casablanca
#    boost_system
#    boost_filesystem
#    boost_program_options
#    boost_date_time
)
