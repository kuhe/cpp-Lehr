
#ifndef CPPREF_BINARYHEAP_IMPL_H
#define CPPREF_BINARYHEAP_IMPL_H

#include "BinaryHeap.h"

namespace Lehr {

    template<typename T>
    BinaryHeap<T>::BinaryHeap() {}

    template<typename T>
    BinaryHeap<T>& BinaryHeap<T>::push(T &item) {
        // todo
        return *this;
    }

    template<typename T>
    T* BinaryHeap<T>::peek() {
        return root;
    }

    template<typename T>
    BinaryHeap<T>& BinaryHeap<T>::pop() {
        // todo
        return *this;
    }

    template<typename T>
    void BinaryHeap<T>::resize(size_t n) {
        data.resize(n);
    }

    template<typename T>
    size_t BinaryHeap<T>::index_of(size_t depth) {
        if (depth <= 1) return 0;
        return (size_t) std::pow(2, depth - 1) - 1;
    }

    template<typename T>
    size_t BinaryHeap<T>::depth_of(size_t index) {

        if (index == 0) return 1;
        if (index < 3) return 2;

        size_t depth = 3;
        size_t max_index = 6;
        size_t power_2 = 8;

        while (max_index < index) {
            depth += 1;
            max_index += power_2;
            power_2 *= 2;
        }
        return depth;
    }

    template<typename T>
    pair<size_t, size_t> BinaryHeap<T>::children(size_t parent) {

        /* This was the reasoning, but it happens to be 2x + 1
        auto depth = depth_of(parent);
        auto index_left = index_of(depth);

        auto offset = parent - index_left;

        size_t left = index_of(depth + 1) + offset * 2;
        size_t right = left + 1;

        return make_pair(left, right);
        */

        auto fold = parent * 2;

        return make_pair(fold + 1, fold + 2);
    }

}

#endif //CPPREF_BINARYHEAP_IMPL_H
