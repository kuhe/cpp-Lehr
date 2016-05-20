
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
            Set<Node<T>*> closed;
            Set<Node<T>*> open;
            open.add(&start);
            Map<Node<T>*, double> g_score; // cost to move to the key node
            Map<Node<T>*, Node<T>*> came_from;
            g_score[&start] = 0;
            decltype(g_score) f_score; // cost of moving through key node to the goal
            f_score[&start] = heuristic(start, goal);

            auto reconstruct_path = [&came_from](Node<T>* current) -> LinkedList<Node<T>*> {
                using Lehr::LinkedList;
                LinkedList<Node<T>*> total_path;
                total_path.push(current);
                while (came_from.contains(current)) {
                    current = came_from[current];
                    total_path.push(current);
                }
                return total_path;
            };

            auto get_lowest_f_score = [&f_score]() -> Node<T>* {
                Node<T>* candidate = nullptr;
                double min = INT_MAX;
                for (auto node : f_score.keys()) {
                    double score = f_score[node];
                    if (score < min) {
                        candidate = node;
                        min = score;
                    }
                }
                return candidate;
            };

            while (!open.empty()) {
                Node<T>* current = get_lowest_f_score();
                if (current == nullptr) {
                    break;
                }
                if (*current == goal) {
                    return reconstruct_path(current);
                }
                open.remove(current);
                closed.add(current);

                auto test = open.size();
                auto test2 = closed.size();

                for (Node<T>*& neighbor : current->nodes) {
                    if (closed.contains(neighbor)) {
                        continue;
                    }

                    auto t1 = neighbor;
                    auto t2 = open.contains(neighbor);

                    // double tentative_g_score = g_score[current];// + current.path(neighbor).size();
                    double tentative_g_score = g_score[current] + heuristic(*current, *neighbor);
                    if (!open.contains(neighbor)) {
                        open.add(neighbor);
                    } else if (tentative_g_score >= g_score[neighbor]) {
                        continue;
                    }
                    came_from[neighbor] = current;
                    g_score[neighbor] = tentative_g_score;
                    f_score[neighbor] = g_score[neighbor] + heuristic(*neighbor, goal);
                }
            }

            LinkedList<Node<T>*> failure;
            return failure;
        }
    };
}

#endif //CPPREF_GRAPH_H
