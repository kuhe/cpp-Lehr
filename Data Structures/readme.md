Data Structure implementations by the learner, under the namespace Lehr (e.g. Lehr::LinkedList)

Trees can be found in the Graphs directory.

### Notes

I feel that the number of graph types is too high to represent each as a class. The inheritance diagram, itself a graph,
would be insanely complex.

Instead, I will opt to construct individual classes for specialist graphs of particular interest, while keeping inheritance shallow
if using it at all.

Candidates for implementation:
````
Graph (nondescript undirected graph)
Self-balancing binary search tree
Heap
Red black tree (?)
Trie
````