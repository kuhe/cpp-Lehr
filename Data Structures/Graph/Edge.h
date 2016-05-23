#ifndef CPPREF_EDGE_H
#define CPPREF_EDGE_H

#include "_graph_common.h"

namespace Lehr {
    template <typename T, typename M>
    class Edge {
    public:
        M weight = 1;
        enum flow { BOTH, LEFT, RIGHT };
        flow direction = BOTH;

        Node<T>* left;
        Node<T>* right;

        Edge() = delete;

        Edge(Node<T>* l, Node<T>* r, M weight = 1) : weight(weight) {
            left = l;
            right = r;
            l->connect(this);
            l->connect(r);
            r->connect(this);
            r->connect(l);
        }

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

        bool operator == (Edge const& edge) {
            return this == &edge;
        }

    };
}

#endif //CPPREF_EDGE_H
