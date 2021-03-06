#include "_run_all.h"

Results results;

namespace Lehr {

    int run_all_tests() {

        cout << "Hello, World!" << endl << endl;
        cout << "C++ version: " << __cplusplus << endl << endl;

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

        cout << "Binary Search Tree: ";
        test_trees();

        cout << "Heap: ";
        test_heap();

        cout << "Fenwick Tree: ";
        test_fenwick();

        cout << "Rule of X: ";
        test_rule_of_X();

        cout << "const: ";
        test_const();

        cout << "Pointer: ";
        test_pointers();

        cout << "concurrency: ";
        test_concurrency();

        cout << "template meta-programming: ";
        test_tmp();

        cout << "\nYay! " << (results.score) << " passed. "
             << (results.failed) << " mysterious failure(s)." << endl;

        // cin.get();

        return 0;
    }

}
