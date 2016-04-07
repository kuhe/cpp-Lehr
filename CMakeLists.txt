cmake_minimum_required(VERSION 3.1)
project(cppRef)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp "Data Structures/Graph/Graph.h" "Data Structures/Graph/_graph_common.h" "Data Structures/Graph/Node.h" "Data Structures/Graph/Edge.h" Tests/test_graph.cpp Tests/test_graph.h "Data Structures/Set/Set.h" "Data Structures/Set/_set_common.h" "Data Structures/Graph/BinarySearchTree/_bst_common.h" "Data Structures/Graph/BinarySearchTree/BinarySearchTree.h" Tests/test_trees.cpp Tests/test_trees.h Tests/test_common.h "Data Structures/Graph/BinarySearchTree/BinarySearchTree.impl.h" Tests/test_rule_of_X.cpp Tests/test_rule_of_X.h Tests/test_const.cpp Tests/test_const.h "Data Structures/Pointer/UniquePointer.impl.h" "Data Structures/Pointer/UniquePointer.h" Tests/test_pointers.cpp Tests/test_pointers.h "Data Structures/Pointer/SharedPointer.h" "Data Structures/Pointer/_pointer_common.h")
add_executable(cppRef ${SOURCE_FILES} "Data Structures/WeightedJob.cpp" "Data Structures/WeightedJob.h" Utilities/vector_util.h Utilities/vector_util.cpp Utilities/string_util.cpp "Data Structures/List/LinkedList.h" Tests/test_lists.h Tests/test_lists.cpp Utilities/_std_symbols.h "Data Structures/List/_list_common.h" "Data Structures/List/ArrayList.h" "Data Structures/List/List.h" "Data Structures/Map/Map.h" Tests/test_map.cpp Tests/test_map.h "Data Structures/Graph/Graph.h" "Data Structures/Graph/Node.h" "Data Structures/Graph/Edge.h" Tests/test_graph.cpp Tests/test_graph.h)

