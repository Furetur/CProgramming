cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Homework1Task11 hw1/1.11.c
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
)
add_executable(
        Homework9Task1 hw9/9.1.c
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
        lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h
        hw9/machine/machine.c hw9/machine/machine.h
)