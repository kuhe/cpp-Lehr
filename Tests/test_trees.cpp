#ifndef CPPREF_TEST_TREES_CPP
#define CPPREF_TEST_TREES_CPP

#include "./test_trees.h"
#include "../Data Structures/List/ArrayList.h"

using Lehr::BinarySearchTree;
using Lehr::ArrayList;

int test_trees() {

    BinarySearchTree<int> tree(0);
    BinarySearchTree<string> str_tree("a");
    BinarySearchTree<int, string> map_tree2(12, "twelve");

    BinarySearchTree<int, int> itree;

    itree[2] = 22;
    itree[3] = 333;

    console_test(itree[2], 22);
    console_test(itree[3], 333);
    console_test(itree.contains(2), true);
    console_test(itree.contains(3), true);
    console_test(itree.contains(333), false);
    console_test(itree.contains(22), false);
    console_test(itree.contains_value(22), true);
    console_test(itree.contains_value(333), true);
    console_test(itree.contains_value(2), false);
    console_test(itree.contains_value(3), false);

    itree[4] = 4444;
    itree[5] = 55555;

    console_test(itree.contains_value(55555), true);
    itree.truncate(4);
    console_test(itree.contains_value(55555), false);
    console_test(itree.contains_value(4444), false);
    console_test(itree.contains_value(333), true);

    itree[6] = 666666;
    itree[7] = 7777777;
    itree[8] = 88888888;

    itree.excise(7);
    console_test(itree.contains(8), true);
    console_test(itree.contains_value(88888888), true);
    console_test(itree.contains(7), false);
    console_test(itree.contains_value(7777777), false);
    console_test(itree.contains(6), true);
    console_test(itree.contains_value(666666), true);

    BinarySearchTree<int, int> itree_copy = itree;
    console_test(itree_copy.contains(8), true);
    console_test(itree_copy.contains(7), false);
    console_test(itree_copy.contains(6), true);
    itree_copy[7] = 7777777;
    console_test(itree.contains(7), false);

    vector<int> keys = {5,6,4,7,3,8,2,9,1};
    for (int k : keys) {
        itree[k] = -k;
        itree_copy[-k] = k;
    }
    vector<int> keys2 = {5,6,4,7,3,8,2,9,1};
    for (int k : keys2) {
        console_test(itree[k], -k);
        console_test(itree.contains(-k), false);
        console_test(itree_copy[-k], k);
    }
    itree.slice(8);
    console_test(itree.contains(7), true); // left branch of 8
    console_test(itree.contains(6), false); // sliced
    console_test(itree.contains(8), true); // now the root
    console_test(itree.contains(9), true); // right branch of 8
    console_test(itree.root_key(), 8);

    vector<int> iteration_order_expected_integers = {7, 8, 9};
    int n = 0;
    for (auto i : itree) {

        console_test(i.first, iteration_order_expected_integers[n++]);

    }

    BinarySearchTree<int, string> iteration_tree;
    iteration_tree[5] = "five";
    iteration_tree[4] = "four";
    iteration_tree[33] = "thirty-three";
    iteration_tree[2] = "two";
    iteration_tree[11] = "eleven";
    vector<string> iteration_order_expected = {"two", "four", "five", "eleven", "thirty-three"};

    {
        ArrayList<int> schluesseln = iteration_tree.keys();
        console_test(schluesseln.size(), 5);
        console_test(iteration_tree.size(), 5);
    }

    n = 0;
    for (auto i : iteration_tree) {
        console_test(iteration_order_expected[n++], i.second);
    }
    console_test(iteration_tree.depth(), 3);

    BinarySearchTree<int, string> map_tree;

    string fourteen = "fourteen";
    string twenty = "twenty";

    map_tree[14] = fourteen;
    map_tree[20] = twenty;

    string test1 = map_tree[14];
    string test2 = map_tree[20];

    console_test(fourteen, test1);
    console_test(twenty, test2);

    str_tree["excelsior!"];
    console_test(str_tree.contains("excelsior!"), true);


    cout << endl;
    return 0;
}

#endif //CPPREF_TEST_TREES_CPP