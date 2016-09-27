#include "./test_heap.h"

using IntBinaryHeap = Lehr::BinaryHeap<int>;

int test_heap() {

    {
        IntBinaryHeap h;
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

        console_test(h.index_of(1), 0);
        console_test(h.index_of(2), 1);
        console_test(h.index_of(3), 3);
        console_test(h.index_of(4), 7);
        console_test(h.index_of(5), 15);
        console_test(h.index_of(6), 31);
        console_test(h.index_of(7), 63);
        console_test(h.index_of(8), 127);
        console_test(h.index_of(12), 2047);
        console_test(h.index_of(16), 32767);

        console_test(h.children(0).first, 1);
        console_test(h.children(0).second, 2);
        console_test(h.children(6).first, 13);
        console_test(h.children(6).second, 14);
        console_test(h.children(10).first, 21);
        console_test(h.children(10).second, 22);
        console_test(h.children(25).first, 51);
        console_test(h.children(25).second, 52);
    }

    cout << endl;
    return 0;

}