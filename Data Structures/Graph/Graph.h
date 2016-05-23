#ifndef CPPREF_GRAPH_H
#define CPPREF_GRAPH_H

#include "_graph_common.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {
    template <typename T, typename M>
    class Graph {
    protected:
        Set<Node<T>*> nodes;
        Set<Edge<T>*> edges;
    public:
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

        // @see Wikipedia: A* search algorithm
        LinkedList<Node<T>*> A_star(Node<T>& start, Node<T>& goal, function<double(Node<T>& start, Node<T>& goal)> heuristic);

        // Dijkstra's pathfinder
        LinkedList<Node<T>*> path(Node<T>& start, Node<T>& goal);

    protected:
        // assisting the pathfinder methods by using serializable keys instead of objects
        // where T node::item is deliberately unique for each Node, representing its location on the graph.
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
