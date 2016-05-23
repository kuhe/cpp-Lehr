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
        LinkedList<Node<T>*> A_star(Node<T>& start, Node<T>& goal, function<double(Node<T>& start, Node<T>& goal)> heuristic) {

            read_node_map(&start);
            using node_value_t = decltype(start.item);

            BinarySearchTree<node_value_t, Node<T>*> closed;
            BinarySearchTree<node_value_t, Node<T>*> open;
            open[(node_value_t) start] = &start;

            Map<node_value_t, double> g_score; // cost to move to the key node
            Map<node_value_t, Node<T>*> came_from;
            g_score[(node_value_t) start] = 0;

            Map<node_value_t, double> f_score; // cost of moving through key node to the goal
            f_score[(node_value_t) start] = heuristic(start, goal);

            auto reconstruct_path = [&came_from](Node<T>* current) -> LinkedList<Node<T>*> {
                using Lehr::LinkedList;
                using node_value_t = decltype(current->item);

                LinkedList<Node<T>*> total_path;
                total_path.push(current);
                while (came_from.contains((node_value_t)(*current))) {
                    current = came_from[(node_value_t)(*current)];
                    total_path.push(current);
                }
                return total_path;
            };

            auto get_lowest_f_score = [&f_score, &open, this]() -> Node<T>* {
                Node<T>* candidate = nullptr;
                double min = INT_MAX;
                for (auto key : open.keys()) {
                    double score = f_score[key];
                    if (score < min) {
                        candidate = node_map[key];
                        min = score;
                    }
                }
                return candidate;
            };

            const int neighbor_distance = 1;

            int n = 100;

            while (!open.empty() && n-- > 0) {
                Node<T>* current = get_lowest_f_score();
                if (current == nullptr) {
                    break;
                }
                if (*current == goal) {
                    return reconstruct_path(current);
                }
                open.excise((node_value_t)(*current));
                closed[(node_value_t)(*current)] = current;
                for (auto neighbor : current->nodes) {
                    if (closed.contains(neighbor->item)) {
                        continue;
                    }
                    double tentative_g_score = g_score[current->item] + neighbor_distance;
                    if (!open.contains(neighbor->item)) {
                        open[(node_value_t)(*neighbor)] = neighbor;
                    } else if (tentative_g_score >= g_score[(node_value_t)(*neighbor)]) {
                        continue;
                    }
                    came_from[neighbor->item] = current;
                    g_score[neighbor->item] = tentative_g_score;
                    f_score[neighbor->item] = g_score[neighbor->item] + heuristic(*neighbor, goal);
                }
            }

            LinkedList<Node<T>*> failure;
            return failure;
        }
    protected:
        // assisting the A* method by using more serializable keys instead of objects
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

#endif //CPPREF_GRAPH_H
