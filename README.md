### Learning Reference (GCC C++17)

====

#### The Poor Man's Computer Science Review

lists, hashes, maps, graphs, in the context
of algorithms and data structures, accompanied by `stdout` unit tests.

Learner's implementations under the `Lehr` namespace.

For me, C++ is a difficult language and trying to learn it is like attacking Bruce Lee in a movie: 
you get a real beating, in this case delivered using
dangling pointers, segfaults, the multi-talented `const` keyword, type deduction,
templates and their meta-programming, and incredibly long g++ error messages.


Issues: [https://github.com/kuhe/cpp-Lehr/issues](https://github.com/kuhe/cpp-Lehr/issues)

    Todo
        BRTRee, BST balancing
        What's new in C++14?
        What's new in C++17?

    Horizon
        see 23.2 Container Requirements, refactor to meet requirements


Currently implemented (approximate corresponding Java/C++ library class):

    LinkedList (LinkedList/forward_list)
    ArrayList (ArrayList/vector)
        + Mergesort (virtual)
    Map (HashMap/unordered_map)
    Set (HashSet/unordered_set)
    Graph (?/?)
        + Dijkstra & A*
    BinarySearchTree (TreeMap/map)
    FenwickTree (?/?)
    BinaryHeap (PriorityQueue/priority_queue)
    UniquePointer (?/unique_ptr)
    SharedPointer (?/shared_ptr)


### Code Style Notes

I'll try, unsuccessfully, to follow these guidelines:
- namespace Lehr for my implementations
- types as title case, methods/variables with underscores
- constant reference method parameters
- restrict raw pointer usage outside of data structure implementations
- Limit OO terms in type names (e.g. `List` instead of `IList` or `ListInterface` or `AbstractList`)
- member order: public, protected, private

````
namespace Lehr {
    class MyCoolClass {
    public:
        int my_cool_method(const int& input);
    private:
        bool blah;
    }
}
````
