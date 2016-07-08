### Learning Reference (GCC C++11)

====

#### The Poor Man's Computer Science Revue

Starring lists, hashes, graphs, in the context
of basic algorithms and data structures.

Learner's implementations under the Lehr namespace.

As a bonus, a free beating courtesy of the C++ language, delivered using
dangling pointers, segfaults, the mysterious const keyword, type deduction,
templates and their meta-programming, and a convenient google search index called "any and all g++ error messages".


Issues: [https://github.com/kuhe/cpp-Lehr/issues](https://github.com/kuhe/cpp-Lehr/issues)

    Todo
        initializer list for List construction
        BRTRee, BST balancing
        copy-and-swap idiom
        weak smart pointers
        Heap
        Concurrency

    Cleanup
        detect <thread> support (optional test)
        stack allocation of ArrayList (no constructor call?) results in faulty delete in destructor
        How do you use an arbitrary object as a Map key? What if it has no serialization method?
        Add sortable detection to ArrayList type

    Horizon
        see 23.2 Container Requirements, refactor to meet requirements


Currently implemented (approximate corresponding Java/C++ library class):

    LinkedList (LinkedList/forward_list)
    ArrayList (ArrayList/vector)
    Map (HashMap/unordered_map)
    Set (HashSet/unordered_set)
    Graph (/)
        + Dijkstra & A*
    BinarySearchTree (TreeMap/map)
    UniquePointer (/unique_ptr)
    SharedPointer (/shared_ptr)


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
