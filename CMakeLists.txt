cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_library(
        AllLib
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
        lib/stringutils/stringutils.c lib/stringutils/stringutils.h
        lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h
        lib/stack/stack.h lib/stack/stack.c
        lib/expressions/expressions.c lib/expressions/expressions.h
)

add_executable(Homework1Task11 hw1/1.11.c)
target_link_libraries(Homework1Task11 AllLib)

add_executable(Homework2Task5 hw2/2.5.c)
target_link_libraries(Homework2Task5 AllLib)

add_executable(Homework3Task2 hw3/3.2.c)

add_executable(Homework4Task1 hw4/4.1.c)
target_link_libraries(Homework4Task1 AllLib)

add_executable(Homework5Task1 hw5/5.1.c)
target_link_libraries(Homework5Task1 AllLib)
