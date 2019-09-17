cmake_minimum_required(VERSION 3.1)
project(cppRef)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
        "Data Structures/Graph/_graph_common.h"
        "Data Structures/Graph/Graph.h"
        "Data Structures/Graph/Graph.impl.h"
        "Data Structures/Graph/Node.h"
        "Data Structures/Graph/Edge.h"

        "Data Structures/Graph/BinarySearchTree/_bst_common.h"
        "Data Structures/Graph/BinarySearchTree/BinarySearchTree.h"
        "Data Structures/Graph/BinarySearchTree/BinarySearchTree.impl.h"

        "Data Structures/Graph/Heap/BinaryHeap.h"

        "Data Structures/Graph/FenwickTree/FenwickTree.h"

        "Data Structures/List/_list_common.h"
        "Data Structures/List/ArrayList.h"
        "Data Structures/List/LinkedList.h"
        "Data Structures/List/List.h"

        "Data Structures/Map/_map_common.h"
        "Data Structures/Map/Map.h"

        "Data Structures/Pointer/_pointer_common.h"
        "Data Structures/Pointer/UniquePointer.h"
        "Data Structures/Pointer/UniquePointer.impl.h"
        "Data Structures/Pointer/SharedPointer.h"

        "Data Structures/Set/_set_common.h"
        "Data Structures/Set/Set.h"

        "Data Structures/WeightedJob.h"
        "Data Structures/WeightedJob.cpp"

        Tests/test_common.h
        Tests/test_const.h
        Tests/test_const.cpp
        Tests/test_graph.h
        Tests/test_graph.cpp
        Tests/test_lists.h
        Tests/test_lists.cpp
        Tests/test_trees.h
        Tests/test_trees.cpp
        Tests/test_map.h
        Tests/test_map.cpp
        Tests/test_pointers.h
        Tests/test_pointers.cpp
        Tests/test_rule_of_X.h
        Tests/test_rule_of_X.cpp
        Tests/test_trees.h
        Tests/test_trees.cpp
        Tests/test_threads.h
        Tests/test_threads.cpp
        Tests/test_heap.h
        Tests/test_heap.cpp
        Tests/test_fenwick.h
        Tests/test_fenwick.cpp
        Tests/test_tmp.h
        Tests/test_tmp.cpp
        Tests/_all_tests.h
        Tests/_run_all.cpp
        Tests/_run_all.h

        Utilities/_std_symbols.h
        Utilities/vector_util.h
        Utilities/vector_util.cpp
        Utilities/string_util.h
        Utilities/string_util.cpp

        main.cpp
        )

add_executable(cppRef ${SOURCE_FILES})