#ifndef CPPREF_EDGE_H
#define CPPREF_EDGE_H

#include "_graph_common.h"

namespace Lehr {

    /**
     * An edge for the object representation of a graph. M is the measure unit for weights of edges, e.g. int.
     */
    template <typename T, typename M>
    class Edge {
    public:
        M weight = 1;
        enum flow { BOTH, LEFT, RIGHT };

        /**
         * Incomplete implementation for the generalization of a directed graph.
         */
        flow direction = BOTH;

        Node<T>* left;
        Node<T>* right;

        /**
         * An edge can only exist between two nodes.
         */
        Edge() = delete;

        Edge(Node<T>* l, Node<T>* r, M weight = 1) : weight(weight) {
            left = l;
            right = r;
            l->connect(this);
            l->connect(r);
            r->connect(this);
            r->connect(l);
        }

        /**
         * Returns the other node in the edge if this edge is connected, otherwise returns the input node.
         */
        Node<T>* other(Node<T>* node) {
            if (contains(node)) {
                if (left == node) {
                    return right;
                }
                return left;
            }
            return node;
        }

        bool contains(Node<T>* node) {
            return *left == *node || *right == *node;
        }

        /**
         * Only equal to itself.
         */
        bool operator == (Edge const& edge) {
            return this == &edge;
        }

    };
}

#endif //CPPREF_EDGE_H
