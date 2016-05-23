#include "test_graph.h"

using Lehr::Graph;
using Lehr::Node;
using Lehr::Edge;
using Lehr::Map;

int test_graph() {
    {
        Graph<int> graph;
        Node<int> n1, n2, n3, n4, n5;
        Edge<int> edge(&n1, &n4);

        graph.addEdge(&n1, &n2);
        graph.addEdge(&edge);
        graph.addNode(&n5);

        graph.connect(&n1, &n3);

        bool test1 = n1.adjacent(&n2);
        bool test2 = n2.adjacent(&n1);
        bool test3 = n1.adjacent(&edge);
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

        for (int x = 1; x < 7; x++) {
            for (int y = 1; y < 7; y++) {
                int key = x * 10 + y;
                if (x > 2 && x < 6 && y == 5) {
                    continue;
                }
                if (y > 2 && y < 6 && x == 5) {
                    continue;
                }
                Node<int>* node = new Node<int>(key);
                nodes[key] = node;

                if (x > 1 && nodes.contains(key - 10)) { // connect left
                    Node<int>* left = nodes[key - 10];
                    graph.addEdge(left, node);
                }
                if (y > 1 && nodes.contains(key - 1)) { // connect down
                    Node<int>* down = nodes[key - 1];
                    graph.addEdge(down, node);
                }
            }
        }

        console_test(nodes.keys().size(), 31);

        console_test(nodes[11]->connects(nodes[66]));
        console_test(nodes[66]->connects(nodes[11]));
        console_test(nodes[61]->connects(nodes[16]));

        console_test(nodes[16]->connects(nodes[11]));
        console_test(nodes[11]->connects(nodes[61]));
        console_test(nodes[16]->connects(nodes[61]));

        // decltype(auto) // C++14
        function<double(Node<int>& start, Node<int>& goal)> // C++11
                heuristic = [](Node<int>& start, Node<int>& goal) -> double {
            double l = start.item/10 - goal.item/10;
            double w = start.item%10 - goal.item%10;
            return sqrt(l * l + w * w);
        };

        auto path = graph.A_star(*nodes[11], *nodes[66], heuristic);
        console_test(path.size() >= 10 && path.size() <= 12);
    }

    cout << endl;
    return 0;
};

