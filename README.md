### Learning Reference (GCC C++11)

====

#### The Poor Man's Computer Science Revue

Learning lists, hashes, graphs, in the context
of basic algorithms and data structures.

Adding learner's implementations of common data structures under the Lehr namespace.

Thus, additionally serving as (for free) a good old-fashioned beat down courtesy of the C++ language, via
pointers, references to pointers, pointers to pointers, segfaults, the mysterious const keyword, type deduction,
templates, and a convenient google search index called "any and all g++ error messages".


todo:

    Todo
        move semantics for Lists
        Dijkstra and A* on graphs
        more specialty graphs (e.g. BRTree)
        copy-and-swap idiom
        weak smart pointers

    Cleanup
        stack allocation of ArrayList (no constructor call?) results in faulty delete in destructor
        harden (hash) sets

    Horizon
        see 23.2 Container Requirements, refactor to meet requirements


Currently implemented:

    LinkedList, ArrayList from virtual List
    Lehr::Map, Lehr::Set
    Lehr::Graph
    Lehr::BinarySearchTree
    Lehr::UniquePointer, Lehr::SharedPointer


### Code Style Notes

I'll try, unsuccessfully, to follow these guidelines:
- namespace Lehr for my implementations
- types as title case, methods/variables with underscores
- constant input references? (yeah, right...)
- restrict pointer usage outside of data structure implementations
- Limit OO terms in type names (e.g. List instead of IList or ListInterface or AbstractList)
- member order: public, protected, private

````
namespace Lehr {
    class MyCoolClass {
    public:
        int my_cool_method(const int& input);
    protected:
        bool blah;
    }
}
````
