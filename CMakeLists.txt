cmake_minimum_required(VERSION 3.7)
project(itop4412Codes)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES 04.time.c 08.1_pipe.c 09.msgsend.c 09.msgrcv.c 09.2_sighello.c 09.03_semun.c 09.05shm1.c shm_com.h 09.05shm2.c 10.1C1.c.c 10.1S1.c.c)
add_library(itop4412Codes ${SOURCE_FILES})