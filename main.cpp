#include <iostream>
#include "Tests/_all_tests.h"
Results results;

int main() {

    cout << "Hello, World!" << endl << endl;

    cout << "List: ";
    using ArrayListString = Lehr::ArrayList<string>;
    using ArrayListInt = Lehr::ArrayList<int>;
    test_lists<ArrayListString, ArrayListInt>();
    using LinkedListString = Lehr::LinkedList<string>;
    using LinkedListInt = Lehr::LinkedList<int>;
    test_lists<LinkedListString, LinkedListInt>();

    cout << "Map: ";
    test_map();

    cout << "Graph: ";
    test_graph();

    cout << "Tree: ";
    test_trees();

    cout << "Rule of X: ";
    test_rule_of_X();

    cout << "const: ";
    test_const();

    cout << "Pointer: ";
    test_pointers();
    
    cout << "threads: ";
    test_threads();

    cout << "\nYay! " << (results.score) << " passed. "
         << (results.failed) << " mysterious failure(s)." << endl;

    // cin.get();

    return 0;
}