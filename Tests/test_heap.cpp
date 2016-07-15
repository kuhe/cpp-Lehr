#include "./test_heap.h"

int test_heap() {

    using Lehr::BinaryHeap;

    {
        BinaryHeap<int> h;
        h.resize(20);
        console_test(h.depth_of(0), 1);
        console_test(h.depth_of(1), 2);
        console_test(h.depth_of(2), 2);
        console_test(h.depth_of(3), 3);
        console_test(h.depth_of(4), 3);
        console_test(h.depth_of(5), 3);
        console_test(h.depth_of(6), 3);
        console_test(h.depth_of(7), 4);
        console_test(h.depth_of(8), 4);
        console_test(h.depth_of(500), 9);
        console_test(h.depth_of(50000), 16);
    }

    cout << endl;
    return 0;

}