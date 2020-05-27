cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework3Task2 hw3/3.2.c)
add_executable(
        Homework1Task11 hw1/1.11.c
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
)
add_executable(
        Homework2Task5 hw2/2.5.c
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/stringutils/stringutils.c lib/stringutils/stringutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
)
add_executable(
        Homework4Task1 hw4/4.1.c
        lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h
)
