
#ifndef CPPREF_EDGE_H
#define CPPREF_EDGE_H

#include "_graph_common.h"

namespace Lehr {
    template <typename T>
    class Edge {
    public:
        double weight;
        Node<T>* left;
        Node<T>* right;
        Edge(Node<T>* l, Node<T>* r) : left(l), right(r) {
            l->connect(this);
            r->connect(this);
        }
        Edge(T* l, T* r) {
            Node<T> a, b;
            a = *l;
            b = *r;
            Edge(&a, &b); // C++11 constructor delegation
        }

        Node<T>* other(Node<T>* node) {
            if (contains(node)) {
                if (*left == *node) {
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
