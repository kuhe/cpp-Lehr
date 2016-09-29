#ifndef CPPREF_HEAP_H
#define CPPREF_HEAP_H

#include <cmath>
#include "../../../Utilities/_std_symbols.h"
#include "../../List/ArrayList.h"

namespace Lehr {

    /**
     * A classic binary heap backed by an array.
     */
    template<typename T>
    class BinaryHeap {

    public:

        /**
         * The default comparator is "less than", i.e. a min-heap.
         */
        BinaryHeap();

        /**
         * Satisfying this comparator will place the advantaged lhs item at the top of the heap.
         */
        BinaryHeap(function<bool(const T& lhs, const T& rhs)> comparator) : comparator(comparator) {};

        BinaryHeap& push(T& item);

        /**
         * A reference to the top item.
         */
        T& peek();

        /**
         * Remove the top item.
         */
        BinaryHeap& pop();

        /**
         * Reallocate the backing store. This would possibly truncate the structure.
         */
        void resize(size_t n);

        size_t size();

        bool empty();

    protected:

        bool empty_ = true;

        size_t last_ = 0;

        size_t size_ = 0;

        ArrayList<T> data_;

        size_t index_of(size_t depth);

        size_t depth_of(size_t index);

        pair<size_t, size_t> children(size_t parent);

        size_t parent(size_t child);

        function<bool(const T& lhs, const T& rhs)> comparator = [](const T& lhs, const T& rhs) -> bool {
            return lhs < rhs;
        };

    private:

        friend int ::test_heap();

    };

}

#include "./BinaryHeap.impl.h"

#endif //CPPREF_HEAP_H
