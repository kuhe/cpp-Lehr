#include <iostream>
#include "Tests/test_lists.h"
#include "Tests/test_map.h"
#include "Tests/test_graph.h"
#include "Tests/test_trees.h"
#include "Tests/test_rule_of_X.h"
#include "Tests/test_const.h"
#include "Tests/test_pointers.h"
#include "Tests/test_threads.h"
Results results;

int main() {

    cout << "Hello, World!" << endl << endl;

    cout << "List: ";
    using al_str = Lehr::ArrayList<string>;
    using al_int = Lehr::ArrayList<int>;
    int test = test_lists<al_str, al_int>();
    using ll_str = Lehr::LinkedList<string>;
    using ll_int = Lehr::LinkedList<int>;
    test = test_lists<ll_str, ll_int>();

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
    
    cout << "threads: ";
    int test8 = test_threads();

    cout << "\nYay! " << (results.score) << " passed. "
         << (results.failed) << " mysterious failure(s)." << endl;

    // cin.get();

    return 0;
}