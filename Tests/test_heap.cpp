#include "./test_heap.h"

using Lehr::BinaryHeap;

namespace LehrTest {
    template<typename T>
    class TestHeap : protected BinaryHeap<T> {
    public:
        size_t test_depth_of(size_t index) {
            return BinaryHeap<T>::depth_of(index);
        }
        size_t test_index_of(size_t depth) {
            return BinaryHeap<T>::index_of(depth);
        }
        void test_resize(size_t size) {
            BinaryHeap<T>::resize(size);
        };
    };
}

int test_heap() {

    {
        LehrTest::TestHeap<int> h;
        h.test_resize(20);
        console_test(h.test_depth_of(0), 1);
        console_test(h.test_depth_of(1), 2);
        console_test(h.test_depth_of(2), 2);
        console_test(h.test_depth_of(3), 3);
        console_test(h.test_depth_of(4), 3);
        console_test(h.test_depth_of(5), 3);
        console_test(h.test_depth_of(6), 3);
        console_test(h.test_depth_of(7), 4);
        console_test(h.test_depth_of(8), 4);
        console_test(h.test_depth_of(500), 9);
        console_test(h.test_depth_of(50000), 16);

        console_test(h.test_index_of(1), 0);
        console_test(h.test_index_of(2), 1);
        console_test(h.test_index_of(3), 3);
        console_test(h.test_index_of(4), 7);
        console_test(h.test_index_of(5), 15);
        console_test(h.test_index_of(6), 31);
        console_test(h.test_index_of(7), 63);
        console_test(h.test_index_of(8), 127);
        console_test(h.test_index_of(12), 2047);
        console_test(h.test_index_of(16), 32767);
    }

    cout << endl;
    return 0;

}