cmake_minimum_required(VERSION 3.7)
project(itop4412Codes)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES 04.time.c 08.1_pipe.c 09.msgsend.c 09.msgrcv.c)
add_library(itop4412Codes ${SOURCE_FILES})