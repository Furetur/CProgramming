cmake_minimum_required(VERSION 3.15)
project(Homework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework hw9/9.1.c lib/arrayutils/arrayutils.c lib/arrayutils/arrayutils.h lib/stringutils/stringutils.c lib/stringutils/stringutils.h lib/numberutils/numberutils.c lib/numberutils/numberutils.h lib/commonutils/commonutils.c lib/commonutils/commonutils.h lib/maxheap/maxheap.c lib/maxheap/maxheap.h lib/heapsort/heapsort.c lib/heapsort/heapsort.h lib/vector2d/vector2d.c lib/vector2d/vector2d.h lib/hashtable/hashtable.c lib/hashtable/hashtable.h lib/linkedlist/linkedlist.c lib/linkedlist/linkedlist.h lib/stack/stack.h lib/stack/stack.c lib/expressions/expressions.c lib/expressions/expressions.h lib/avltree/avltree.h lib/avltree/avltree.c lib/pair/pair.c lib/pair/pair.h lib/graph/graph.c lib/graph/graph.h hw8/countrydata/countrydata.c hw8/countrydata/countrydata.h hw8/worlddata/worlddata.c hw8/worlddata/worlddata.h hw9/machine/machine.c hw9/machine/machine.h)