#ifndef CPPREF_GRAPH_COMMON_H_H
#define CPPREF_GRAPH_COMMON_H_H

#include "../List/LinkedList.h"
#include "../Set/_set_common.h"
#include "./BinarySearchTree/_bst_common.h"

namespace Lehr {
    template <typename T, typename M = double>
    class Node;
    template <typename T, typename M = double>
    class Edge;
    template <typename T, typename M = double>
    class Graph;
}

#include "Node.h"
#include "Edge.h"
#include "Graph.h"

#endif //CPPREF_GRAPH_COMMON_H_H
