cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework hw2/2.5.c lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h lib/stringutils/stringutils.c lib/stringutils/stringutils.h)