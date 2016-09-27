#ifndef CPPREF_HEAP_H
#define CPPREF_HEAP_H

#include <cmath>
#include "../../../Utilities/_std_symbols.h"
#include "../../List/ArrayList.h"

namespace Lehr {

    template<typename T>
    class BinaryHeap {

    public:

        BinaryHeap();

        BinaryHeap& push(T& item);

        T* peek();

        BinaryHeap& pop();

        void resize(size_t n);

    protected:

        T* root = nullptr;

        size_t depth = 0;

        ArrayList<T> data;

        size_t index_of(size_t depth);

        size_t depth_of(size_t index);

        pair<size_t, size_t> children(size_t parent);

    private:

        friend int ::test_heap();

    };

}

#include "./BinaryHeap.impl.h"

#endif //CPPREF_HEAP_H
