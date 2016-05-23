#ifndef CPPREF_GRAPH_IMPL_H_H
#define CPPREF_GRAPH_IMPL_H_H

#include "Graph.h"

namespace Lehr {

    template<typename T, typename M>
    LinkedList<Node<T>*> Graph<T, M>::A_star(Node<T>& start, Node<T>& goal, function<double(Node<T>& start, Node<T>& goal)> heuristic) {

        read_node_map(&start);
        using node_value_t = decltype(start.item);

        BinarySearchTree<node_value_t, Node<T>*> closed;
        BinarySearchTree<node_value_t, Node<T>*> open;
        open[(node_value_t) start] = &start;

        Map<node_value_t, double> g_score; // cost to move to the key node
        Map<node_value_t, Node<T>*> came_from;
        g_score[(node_value_t) start] = 0;

        BinarySearchTree<double, LinkedList<node_value_t>> f_score; // cost of moving through key node to the goal
        f_score[heuristic(start, goal)].push((node_value_t) start);

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

        auto get_lowest_open_f_score = [&f_score, &open, this]() -> Node<T>* {
            for (auto listItem : f_score) {
            for (auto node_coordinates : listItem.second) {
                if (open.contains(node_coordinates)) {
                    return node_map[node_coordinates];
                }
            }
        }
            return nullptr;
        };

        const int neighbor_distance = 1;

        while (!open.empty()) {
            Node<T>* current = get_lowest_open_f_score();
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
                f_score[g_score[neighbor->item] + heuristic(*neighbor, goal)].push(neighbor->item);
            }
        }

        LinkedList<Node<T>*> failure;
        return failure;
    }

    template<typename T, typename M>
    LinkedList<Node<T>*> Graph<T, M>::path(Node<T>& start, Node<T>& goal) {
        read_node_map(&start);
        using coord_t = decltype(start.item);
        using distance_t = M;

        Map<coord_t, Node<T>*> unvisited;

        Map<coord_t, distance_t> distance;
        Map<coord_t, distance_t> previous;

        distance_t max_distance = INT_MAX;
        if (is_same<distance_t, long double>::value) {
            max_distance = LONG_MAX;
        };

        for (auto coord : node_map.keys()) {
            distance[coord] = max_distance;
            unvisited[coord] = node_map[coord];
        }

        distance[(coord_t) start] = 0;

        auto get_closest_unvisited = [&unvisited, &distance, max_distance]() -> Node<T>* {
            using coord_t = decltype(start.item);
            Node<T>* candidate = nullptr;
            distance_t min = max_distance;
            for (auto coord : unvisited.keys()) {
                Node<coord_t>* node = unvisited[coord];
                if (distance[(coord_t)(*node)] < min) {
                    min = distance[(coord_t)(*node)];
                    candidate = node;
                }
            }
            return candidate;
        };

        while (!unvisited.empty()) {
            Node<T>* context = get_closest_unvisited();
            if (context == &goal) {
                break;
            }
            unvisited - context->item;
            for (auto node : context->nodes) {
                distance_t candidate_distance = distance[(coord_t)(*context)] + context->distance(node);
                if (candidate_distance < distance[(coord_t)(*node)]) {
                    distance[(coord_t)(*node)] = candidate_distance;
                    previous[(coord_t)(*node)] = (coord_t)(*context);
                }
            }
        }

        LinkedList<Node<T>*> path;
        auto context = goal;
        while(previous.contains((coord_t) context)) {
            path.unshift(&context);
            context = previous[(coord_t) context];
        }
        return path;
    }
}


#endif //CPPREF_GRAPH_IMPL_H_H
