
#ifndef CPPREF_NODE_H
#define CPPREF_NODE_H

#include "_graph_common.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {
    template <typename T>
    class Node {
    public:
        Node() {}
        Node(T item) : item(item) {}

        T item;

        void connect(Edge<T>* edge) {
            Node<T>* other = edge->other(this);
            if (!adjacent(other)) {
                nodes.push(other);
            }
            if (!adjacent(edge)) {
                edges.push(edge);
            }
        }

        LinkedList<Node<T>*> nodes;
        LinkedList<Edge<T>*> edges;

        bool adjacent(Node<T>* node) {
            return *this == *node || nodes.contains(node);
        }
        bool adjacent(Edge<T>* edge) {
            return edges.contains(edge);
        }
        bool connects(Node<T>* node) {
            visited.clear();
            bool connects = hasConnection(node);
            return connects;
        }
        /**
         * i.e. path exists to a node in the edge
         */
        bool connects(Edge<T>* edge) {
            return connects(edge->left); // the other node is by definition connected.
        }

        bool operator == (Node const& node) {
            return this == &node;
        }
        bool operator == (T const& item) {
            return this->item == &item;
        }
        void operator = (T value) {
            item = value;
        }
    protected:
        Set<Node<T>*> visited;
        /**
         * potentially multi-step path exists to the node
         */
        bool hasConnection(Node<T>* node) {
            bool connected;
            if (adjacent(node)) {
                return true;
            }
            for (int i = 0; i < nodes.size(); i++) {
                Node<T>* n = nodes[i];
                bool test = visited.contains(n);
                if (!visited.contains(n)) {
                    visited.add(n);
                    connected = n->hasConnection(node);
                    if (connected)
                        return true;
                }
            }
            return false;
        }
    };
}

#endif //CPPREF_NODE_H
