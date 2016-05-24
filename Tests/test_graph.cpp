#include "test_graph.h"

using Lehr::Graph;
using Lehr::Node;
using Lehr::Edge;
using Lehr::Map;

int test_graph() {
    {
        Graph<int> graph;
        Node<int> n1, n2, n3, n4, n5;

        graph.addEdge(&n1, &n2);
        graph.addEdge(&n1, &n4);
        graph.addNode(&n5);

        graph.addEdge(&n1, &n3);

        bool test1 = n1.adjacent(&n2);
        bool test2 = n2.adjacent(&n1);
        bool test3 = n1.adjacent(n1.edge_to(&n4));
        bool test4 = n3.adjacent(&n1);
        bool test5 = n4.adjacent(&n1);
        bool test6 = !n4.adjacent(&n2);
        bool test7 = n4.connects(&n3);
        bool test8 = !n3.connects(&n5);

        console_test(test1);
        console_test(test2);
        console_test(test3);
        console_test(test4);
        console_test(test5);
        console_test(test6);
        console_test(test7);
        console_test(test8);
    }

    {
        /**
         * 6         E
         * 5   x x x
         * 4       x
         * 3       x
         * 2
         * S 2 3 4 5 6
         *
         * path find S -> E
         *
         */
        Graph<int> graph;
        Map<int, Node<int>*> nodes;

        for (int x = 1; x < 16; x++) {
            for (int y = 1; y < 16; y++) {
                int key = x * 100 + y;
                if (x > 7 && x < 13 && y == 12) {
                    continue;
                }
                if (y > 7 && y < 13 && x == 12) {
                    continue;
                }
                Node<int>* node = new Node<int>(key);
                nodes[key] = node;

                if (x > 1 && nodes.contains(key - 100)) { // connect left
                    Node<int>* left = nodes[key - 100];
                    graph.addEdge(left, node);
                }
                if (y > 1 && nodes.contains(key - 1)) { // connect down
                    Node<int>* down = nodes[key - 1];
                    graph.addEdge(down, node);
                }
            }
        }

        console_test(nodes.keys().size(), 216);

        console_test(nodes[ 101]->connects(nodes[1515]));
        console_test(nodes[1515]->connects(nodes[ 101]));
        console_test(nodes[1501]->connects(nodes[ 115]));

        console_test(nodes[ 106]->connects(nodes[ 101]));
        console_test(nodes[ 101]->connects(nodes[1501]));
        console_test(nodes[ 106]->connects(nodes[1501]));

        // decltype(auto) // C++14
        function<double(Node<int>& start, Node<int>& goal)> // C++11
                heuristic = [](Node<int>& start, Node<int>& goal) -> double {
            double l = start.item/100 - goal.item/100;
            double w = start.item%100 - goal.item%100;
            return sqrt(l * l + w * w);
        };

        auto path = graph.A_star(*nodes[ 101], *nodes[1515], heuristic);
        console_test(path.size() >= 28 && path.size() <= 34);

        console_test(nodes[ 101]->distance(nodes[ 102]), 1);
        console_test(nodes[ 102]->distance(nodes[ 202]), 1);

        auto path2 = graph.path(*nodes[ 101], *nodes[1515]);
        console_test(path2.size(), 28);
    }

    cout << endl;
    return 0;
};

