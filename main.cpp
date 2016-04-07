#include <iostream>
#include "Tests/test_lists.h"
#include "Tests/test_map.h"
#include "Tests/test_graph.h"
#include "Tests/test_trees.h"
#include "Tests/test_rule_of_X.h"
#include "Tests/test_const.h"
#include "Tests/test_pointers.h"
Results results;

int main() {

    cout << "Hello, World!" << endl << endl;

    cout << "List: ";
    int test = test_lists();
    cout << "Map: ";
    int test2 = test_map();
    cout << "Graph: ";
    int test3 = test_graph();
    cout << "Tree: ";
    int test4 = test_trees();
    cout << "Rule of X: ";
    test_rule_of_X();
    cout << "const: ";
    test_const();
    cout << "Pointer: ";
    int test7 = test_pointers();

    cout << "\nYay! " << to_string(results.score) << " passed. " << to_string(results.failed) << " mysterious failure(s)." << endl;

    // cin.get();
    return 0;
}