#ifndef CPPREF_HEAP_H
#define CPPREF_HEAP_H

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
        ArrayList<T> data;

        size_t depth(size_t position) {
            // todo
            return 0;
        }

        pair<size_t, size_t> children(size_t parent) {
            pair<size_t, size_t> kids;
            // todo
            return kids;
        }

    };

}

#endif //CPPREF_HEAP_H
