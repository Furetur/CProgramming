cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework hw2/2.5.c lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h lib/stringutils/stringutils.c lib/stringutils/stringutils.h lib/numberutils/numberutils.c lib/numberutils/numberutils.h lib/commonutils/commonutils.c lib/commonutils/commonutils.h lib/maxheap/maxheap.c lib/maxheap/maxheap.h lib/heapsort/heapsort.c lib/heapsort/heapsort.h lib/vector2d/vector2d.c lib/vector2d/vector2d.h lib/hashtable/hashtable.c lib/hashtable/hashtable.h)