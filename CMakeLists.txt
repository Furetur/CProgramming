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
        lib/avltree/avltree.h lib/avltree/avltree.c
        lib/pair/pair.c lib/pair/pair.h
        lib/graph/graph.c lib/graph/graph.h
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

add_executable(Homework5Task2 hw5/5.2.c)
target_link_libraries(Homework5Task2 AllLib)

add_executable(Homework5Task3 hw5/5.3.c)
target_link_libraries(Homework5Task3 AllLib)

add_executable(Homework6Task1 hw6/6.1.c)
target_link_libraries(Homework6Task1 AllLib)

add_executable(Homework7Task1 hw7/7.1.c)
target_link_libraries(Homework7Task1 AllLib)

add_executable(
        Homework8Task2 hw8/8.2.c
        hw8/countrydata/countrydata.c hw8/countrydata/countrydata.h
        hw8/worlddata/worlddata.c hw8/worlddata/worlddata.h
)
target_link_libraries(Homework8Task2 AllLib)

add_executable(
        Homework9Task1 hw9/9.1.c
        hw9/machine/machine.c hw9/machine/machine.h
)
target_link_libraries(Homework9Task1 AllLib)
