
#ifndef CPPREF_NODE_H
#define CPPREF_NODE_H

#include "_graph_common.h"
#include "Edge.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {

    /**
     * A graph node with T being the item type and M being the measure type of distances between nodes.
     * Here M is generally the same type as the weight type of the edges, as it is the summed weights of the edges
     * of a path that make up its distance.
     *
     * Weight should perhaps have been called "length" or something for edges.
     */
    template <typename T, typename M>
    class Node {
        friend class Edge<T, M>;
        friend class Graph<T, M>;
    public:
        Node() {}
        Node(T item) : item(item) {}

        T item;

        /**
         * Finds the first edge that connects to the target. Doesn't account for the fact that
         * there may be another edge to the same target node.
         */
        Edge<T>* edge_to(Node<T>* target) {
            for (auto ptr : edges) {
                if (ptr->other(this) == target) {
                    return ptr;
                }
            }
            return nullptr;
        }

        /**
         * By definition the target node is either identical or shares an edge.
         */
        bool adjacent(Node<T>* node) {
            return *this == *node || nodes.contains(node);
        }

        /**
         * Notion of adjacency means the edge in question connects this node.
         */
        bool adjacent(Edge<T>* edge) {
            return edges.contains(edge);
        }

        /**
         * Path exists in the graph over any number of edges to the target node, from this one.
         */
        bool connects(Node<T>* node) {
            visited.clear();
            bool connects = has_connection(node);
            return connects;
        }

        /**
         * As above, meaning this node can reach one of the nodes of the target edge.
         */
        bool connects(Edge<T>* edge) {
            return connects(edge->left); // the other node is by definition connected.
        }

        /**
         * Finds the distance to the target if it is adjacent.
         * Otherwise, behavior is poorly defined: -1 is not a good error value for all numeric types (unsigned).
         * todo: find the multi-step distance, not simply the adjacent distance.
         */
        M distance(Node<T>* target) {
            visited.clear();
            auto connection = edge_to(target);
            if (nullptr != connection) {
                return edge_to(target)->weight;
            }
            return -1;
            // todo: find multi-step distance using e.g. Dijkstra's pathfinder
        }

        /**
         * Identity.
         */
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

        LinkedList<Node<T>*> nodes;
        LinkedList<Edge<T>*> edges;

        void connect(Edge<T>* edge) {
            edges.push(edge);
        }

        void connect(Node<T>* node) {
            nodes.push(node);
        }

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
