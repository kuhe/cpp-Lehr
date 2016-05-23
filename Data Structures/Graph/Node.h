
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
        LinkedList<Node<T>*> nodes;
        LinkedList<Edge<T>*> edges;

        void connect(Edge<T>* edge) {
            Node<T>* other = edge->other(this);
            if (!adjacent(other)) {
                nodes.push(other);
            }
            if (!adjacent(edge)) {
                edges.push(edge);
            }
        }
        void connect(Node<T>* node) {
            Edge<T> e(this, node);
            connect(&e);
        }

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
        bool connects(Edge<T>* edge) {
            return connects(edge->left); // the other node is by definition connected.
        }

        bool operator == (const Node& node) {
            return this == &node;
        }
        bool operator == (T const& item) {
            return this->item == &item;
        }
        void operator = (T value) {
            item = value;
        }
        explicit operator T() {
            return item;
        }
    protected:
        /**
         * temporary store for the connection traversal method(s)
         */
        LinkedList<Node<T>*> visited;
        /**
         * (potentially multi-step) path exists to the node
         */
        bool hasConnection(Node<T>* target, Node<T>* origin = nullptr) {
            if (nullptr == origin) {
                origin = this;
            }
            bool connected;
            if (origin->adjacent(target)) {
                return true;
            }
            for (auto branch : origin->nodes) {
                bool already_visited = visited.contains(branch);

                if (!already_visited) {
                    visited.push(branch);
                    connected = hasConnection(target, branch);
                    if (connected)
                        return true;
                }
            }
            return false;
        }
    };
}

#endif //CPPREF_NODE_H
