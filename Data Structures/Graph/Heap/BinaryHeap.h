#ifndef CPPREF_HEAP_H
#define CPPREF_HEAP_H

#include <cmath>
#include "../../../Utilities/_std_symbols.h"
#include "../../List/ArrayList.h"

namespace Lehr {

    template<typename T>
    class BinaryHeap {

    public:

        BinaryHeap() {}

        BinaryHeap& push(T& item) {
            // todo
            return *this;
        }

        T* peek() {
            return root;
        }

        BinaryHeap& pop() {
            // todo
            return *this;
        }

        void resize(size_t n) {
            data.resize(n);
        }

    protected:

        T* root = nullptr;

        size_t depth = 0;

        ArrayList<T> data;

        size_t index_of(size_t depth) {
            if (depth <= 1) return 0;
            if (depth == 2) return 1;
            if (depth == 3) return 3;
            if (depth == 4) return 7;
            if (depth == 5) return 15;

            return (size_t) std::pow(2, depth - 1) - 1;
        }

        size_t depth_of(size_t index) {

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

        pair<size_t, size_t> children(size_t parent) {
            pair<size_t, size_t> kids;
            // todo
            return kids;
        }

    private:

        friend int ::test_heap();

    };

}

#endif //CPPREF_HEAP_H
