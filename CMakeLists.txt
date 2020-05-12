cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Homework7Task1 hw7/7.1.c
        lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h
        lib/commonutils/commonutils.c lib/commonutils/commonutils.h
        lib/avltree/avltree.h lib/avltree/avltree.c
)