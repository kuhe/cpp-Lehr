#ifndef CPPREF_GRAPH_H
#define CPPREF_GRAPH_H

#include "_graph_common.h"

using Lehr::Node; // redundant, but to correct an IDE resolution failure
using Lehr::Edge; // redundant, but to correct an IDE resolution failure

namespace Lehr {
    template <typename T>
    class Graph {
    protected:
        Set<Node<T>*> nodes;
        Set<Edge<T>*> edges;
    public:
        Graph& addNode(Node<T>* node) {
            if (!nodes.contains(node)) {
                nodes.add(node);
            }
            return *this;
        }
        Graph& connect(Node<T>* a, Node<T>* b) {
            if (!a->adjacent(b)) {
                Edge<T> edge(a, b);
                a->connect(&edge);
            }
            return *this;
        }
        Edge<T> addEdge(Node<T>* a, Node<T>* b, int edgeWeight=0) {
            if (!nodes.contains(a)) {
                nodes.add(a);
            }
            if (!nodes.contains(b)) {
                nodes.add(b);
            }
            Edge<T> edge(a, b);
            edge.weight = edgeWeight;
            edges.add(&edge);
            return edge;
        }
        Graph& addEdge(Edge<T>* edge) {
            Node<T>* a, * b;
            a = edge->left;
            b = edge->right;
            if (!nodes.contains(a)) {
                nodes.add(a);
            }
            if (!nodes.contains(b)) {
                nodes.add(b);
            }
            if (!edges.contains(edge)) {
                edges.add(edge);
            }
            return *this;
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
