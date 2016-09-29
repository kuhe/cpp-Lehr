#ifndef CPPREF_GRAPH_H
#define CPPREF_GRAPH_H

#include "_graph_common.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {

    /**
     * A not well thought out object representation of a graph, nodes, and edges.
     */
    template <typename T, typename M>
    class Graph {
    protected:
        Set<Node<T>*> nodes;
        Set<Edge<T>*> edges;
    public:

        /**
         * Because the edges are allocated on the heap by addEdge().
         */
        ~Graph() {
            for (auto ptr : edges.values()) {
                delete ptr;
            }
        }

        typedef M distance_type;
        typedef T node_type;

        Graph& addNode(Node<T>* node) {
            if (!nodes.contains(node)) {
                nodes.add(node);
            }
            return *this;
        }

        /**
         * An edge is only valid between two nodes.
         */
        Edge<T>* addEdge(Node<T>* a, Node<T>* b, M edgeWeight = 1) {
            addNode(a);
            addNode(b);
            auto existing_connection = a->edge_to(b);
            if (existing_connection == nullptr) {
                Edge<T>* edge = new Edge<T>(a, b, edgeWeight);
                edges.add(edge);
                return edge;
            }
            return existing_connection;
        }

        bool contains(Node<T>* node) {
            return nodes.contains(node);
        }

        bool contains(Edge<T>* edge) {
            return edges.contains(edge);
        }

        /**
         * Heuristic type.
         */
        using H = double(Node<T>& start, Node<T>& goal);

        /**
         * A* "A-Star" which I read about on Wikipedia.
         */
        LinkedList<Node<T>*> A_star(Node<T>& start, Node<T>& goal, function<H> heuristic);

        /**
         * Likewise, Dijkstra's pathfinder.
         */
        LinkedList<Node<T>*> path(Node<T>& start, Node<T>& goal);

    protected:

        /**
         * Assisting the pathfinder methods by using serializable keys instead of objects
         * here T node::item is deliberately unique for each Node, representing its location on the graph.
         */
        Map<T, Node<T>*> node_map;

        void read_node_map(Node<T>* from) {
            node_map[from->item] = from;
            for (auto n : from->nodes) {
                if (!node_map.contains(n->item)) {
                    read_node_map(n);
                }
            }
        }

    };
}

#include "Graph.impl.h"

#endif //CPPREF_GRAPH_H
