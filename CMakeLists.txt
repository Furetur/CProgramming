cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework hw5/5.2.c lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h lib/stringutils/stringutils.c lib/stringutils/stringutils.h lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h lib/stack/stack.h lib/stack/stack.c lib/expressions/expressions.c lib/expressions/expressions.h)