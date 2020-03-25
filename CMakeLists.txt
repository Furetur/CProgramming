cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework hw8/8.2.c lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h lib/commonutils/commonutils.c lib/commonutils/commonutils.h lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h lib/pair/pair.c lib/pair/pair.h lib/graph/graph.c lib/graph/graph.h hw8/countrydata/countrydata.c hw8/countrydata/countrydata.h hw8/worlddata/worlddata.c hw8/worlddata/worlddata.h)