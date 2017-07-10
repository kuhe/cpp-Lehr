#ifndef CPPREF_FENWICKTREE_H
#define CPPREF_FENWICKTREE_H


namespace Lehr {

    /**
     *
     * @see https://en.wikipedia.org/wiki/Fenwick_tree
     * @quote "A Fenwick tree or binary indexed tree is a data structure that can efficiently update elements
     * and calculate prefix sums in a table of numbers. This structure was proposed by Peter Fenwick in 1994
     * to improve the efficiency of arithmetic coding compression algorithms."
     *
     * @tparam T transitively summable type.
     */
    template<typename T>
    class FenwickTree {

    public:

        /**
         * Since we will not allow resizing of a tree, the default ctor is deleted
         * in favor of the size ctor.
         */
        FenwickTree() = delete;

        /* rest are default */
        FenwickTree(const size_t size);
        FenwickTree(const size_t size, const T& base);
        FenwickTree(const FenwickTree<T>& other);
        FenwickTree(const FenwickTree<T>&& other);
        FenwickTree<T>& operator =(const FenwickTree<T>& other);
        FenwickTree<T>& operator =(const FenwickTree<T>&& other);
        ~FenwickTree();

        /**
         * @param i index.
         * @return the value at index.
         */
        T operator [](const size_t i);

        /**
         * @param i index.
         * @param j index.
         * @return the sum of values between i and j indices, inclusive.
         */
        T sum(size_t i, size_t j);

        /**
         *
         * @param i index.
         * @param j index.
         * @param base - number to start sum with.
         * @return
         */
        T sum(size_t i, size_t j, T base);

        /**
         * @param value - added at index of underlying array.
         * @param i index.
         * @return instance.
         */
        FenwickTree<T>& add(const T& value, size_t i);

        /**
         * @param value
         * @param i
         * @return
         */
        FenwickTree<T>& set(const T& value, const size_t i);

        /**
         * @return the size of the tree.
         */
        const size_t size();

    private:

        T* data = nullptr;
        const size_t size_ = 0;
        T base;

        /**
         * @param number
         * @return greatest power of 2 at or below the given number. aka least significant 1 bit.
         * This is used for tree traversal.
         *
         * Suppose array incrementing from 1.
         *
         * Tree indices:
         *
         * Binary
         *(000)
         * 001  010   100       1000                10000...
         *      011   101  110  1001 1010 1100
         *                 111       1011 1101 1110
         *                                     1111
         * Decimal
         *  (0)
         *   1    2     4          8                   16...
         *        3     5    6     9   10   12
         *                   7         11   13   14
         *                                       15
         * Values (decimal)
         *  (0)
         *   1    3    10         36                  ***...
         *        3     5   11     9   19   42
         *                   7         11   13   27
         *                                       15
         *
         * Each node's parent is the removal of the least significant 1 bit!
         * Each node's value is the sum of values since its parent.
         *
         * 5(101, 100)     :    5->4 add     5+10 =  15
         * 6(110, 100)     :    6->4 add    11+10 =  21
         * 7(111, 110, 100): 7->6->4 add  7+11+10 =  28
         *
         * 15(1111, 1110, 1100, 1000) : 15->14->12->8 add 15+27+42+36 = 120
         *
         */
        size_t ls1b(const size_t number) noexcept;

    };

    template<typename T>
    FenwickTree<T>::FenwickTree(const size_t size): size_(size) {
        data = new T[size]();
    }

    template<typename T>
    FenwickTree<T>::FenwickTree(const size_t size, const T& base): size_(size), base(base) {
        data = new T[size]();
    }

    template<typename T>
    FenwickTree<T>::FenwickTree(const FenwickTree<T>& other) = default;

    template<typename T>
    FenwickTree<T>::FenwickTree(const FenwickTree<T>&& other) = default;

    template<typename T>
    FenwickTree<T>& FenwickTree<T>::operator =(const FenwickTree<T>& other) = default;

    template<typename T>
    FenwickTree<T>& FenwickTree<T>::operator =(const FenwickTree<T>&& other) = default;

    template<typename T>
    FenwickTree<T>::~FenwickTree() {
        delete[] data;
        data = nullptr;
    };

    template<typename T>
    T FenwickTree<T>::operator [](const size_t i) {
        return sum(i, i);
    }

    template<typename T>
    T FenwickTree<T>::sum(size_t i, size_t j) {
        return sum(i, j, base);
    }

    template<typename T>
    T FenwickTree<T>::sum(size_t i, size_t j, T base) {
        // Inclusive.
        // Take the sum path of j between j and i, and the sum path of i between it and where j terminated.

        j += 1u;

        if (j == 1u) return data[0];

        while (j > i && j != 0u) {
            base += data[j - 1u];
            j -= ls1b(j);
        }

        while (i > j && i != 0u) {
            base -= data[i - 1u];
            i -= ls1b(i);
        }

        return base;
    }

    template<typename T>
    FenwickTree<T>& FenwickTree<T>::add(const T& value, size_t i) {
        // index i and the roots of each next subtree must add [value].

        while (i < size()) {
            data[i] += value;
            i += ls1b(i + 1);
        }

        return *this;
    }

    template<typename T>
    FenwickTree<T>& FenwickTree<T>::set(const T& value, const size_t i) {
        add(value - this->operator [](i), i);
        return *this;
    }

    template<typename T>
    const size_t FenwickTree<T>::size() {
        return size_;
    }

    template<typename T>
    size_t FenwickTree<T>::ls1b(const size_t number) noexcept {
        // This can be achieved in a few ways, the shortest of which, on unsigned numbers, is this:
        return number & -number;

        // equivalently...
        /**
         *
         * number = 52 (110100)
         * We want 100 aka 8.
         *
         * 110100 & (~110100 + 1)
         * 110100 & (001011 + 1)
         * 110100 & 001100
         * 000100 Yes!
         *
         */
        // return number & (~number + 1);

        // very incrementally.
        /*
        unsigned int i = 0;
        while ((number &  (1u << i)) == 0) {
            ++i;
        }
        return 1u << i;
        */
    }

}

#endif //CPPREF_FENWICKTREE_H
