#include <iostream>
#include "Tests/_all_tests.h"
Results results;

int main() {

    cout << "Hello, World!" << endl << endl;

    cout << "List: ";
    using ArrayListString = Lehr::ArrayList<string>;
    using ArrayListInt = Lehr::ArrayList<int>;
    int test = test_lists<ArrayListString, ArrayListInt>();
    using LinkedListString = Lehr::LinkedList<string>;
    using LinkedListInt = Lehr::LinkedList<int>;
    test = test_lists<LinkedListString, LinkedListInt>();

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