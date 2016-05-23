
#ifndef CPPREF_NODE_H
#define CPPREF_NODE_H

#include "_graph_common.h"
#include "Edge.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {
    template <typename T, typename M>
    class Node {
    public:
        Node() {}
        Node(T item) : item(item) {}

        T item;
        LinkedList<Node<T>*> nodes;
        LinkedList<Edge<T>*> edges;

        void connect(Edge<T>* edge) {
            edges.push(edge);
        }
        void connect(Node<T>* node) {
            nodes.push(node);
        }
        Edge<T>* edge_to(Node<T>* target) {
            for (auto ptr : edges) {
                if (ptr->other(this) == target) {
                    return ptr;
                }
            }
            return nullptr;
        }
        bool adjacent(Node<T>* node) {
            return *this == *node || nodes.contains(node);
        }
        bool adjacent(Edge<T>* edge) {
            return edges.contains(edge);
        }
        bool connects(Node<T>* node) {
            visited.clear();
            bool connects = has_connection(node);
            return connects;
        }
        bool connects(Edge<T>* edge) {
            return connects(edge->left); // the other node is by definition connected.
        }
        M distance(Node<T>* target) {
            visited.clear();
            auto connection = edge_to(target);
            if (nullptr != connection) {
                return edge_to(target)->weight;
            }
            return -1;
            // todo: find multi-step distance using dijkstra's pathfinder
        }
        bool operator == (const Node& node) {
            return this == &node;
        }
        bool operator == (const T& item) {
            return this->item == item;
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
        ArrayList<Node<T>*> visited;
        /**
         * (potentially multi-step) path exists to the node
         */
        bool has_connection(Node<T>* target, Node<T>* origin = nullptr) {
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
                    connected = has_connection(target, branch);
                    if (connected)
                        return true;
                }
            }
            return false;
        }

    };
}

#endif //CPPREF_NODE_H
