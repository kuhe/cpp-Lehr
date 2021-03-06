
#ifndef CPPREF_BINARYHEAP_IMPL_H
#define CPPREF_BINARYHEAP_IMPL_H

#include "BinaryHeap.h"

namespace Lehr {

    template<typename T>
    BinaryHeap<T>::BinaryHeap() {}

    template<typename T>
    BinaryHeap<T>& BinaryHeap<T>::push(T& item) {

        auto depth = depth_of(last_);
        auto insertion_index = empty() ? 0 : last_ + 1;

        if (data_.size() < insertion_index - 1) {
            resize(data_.size() * 2);
        }

        data_[insertion_index] = item;
        ++size_;
        if (!empty()) ++last_;
        empty_ = false;

        size_t item_ix = insertion_index;
        size_t parent_ix = parent(item_ix);

        while (!comparator(data_[parent_ix], data_[item_ix])) {

            std::swap(data_[item_ix], data_[parent_ix]);

            item_ix = parent_ix;
            if (item_ix <= 0) {
                break;
            }
            parent_ix = parent(item_ix);

        }

        return *this;
    }

    template<typename T>
    T& BinaryHeap<T>::peek() {
        return data_[0];
    }

    template<typename T>
    BinaryHeap<T>& BinaryHeap<T>::pop() {
        if (!empty()) {

            T& last_item = data_[last_];
            data_[0] = last_item;
            data_.pop();

            --last_;
            --size_;

            if (size() == 0) {
                size_ = 0;
                empty_ = true;
                last_ = 0;
                return *this;
            }

            size_t cursor = 0;
            auto branches = children(cursor);

            while (!comparator(data_[cursor], data_[branches.first]) || !comparator(data_[cursor], data_[branches.second])) {

                size_t comparably_better;
                if (comparator(data_[branches.first], data_[branches.second])) {
                    comparably_better = branches.first;
                } else {
                    comparably_better = branches.second;
                }

                std::swap(data_[cursor], data_[comparably_better]);

                cursor = comparably_better;
                branches = children(cursor);

                if (branches.first > last_ || branches.second > last_) {
                    break;
                }

            }

        }
        return *this;
    }

    template<typename T>
    void BinaryHeap<T>::resize(size_t n) {
        data_.resize(n);
    }

    template<typename T>
    size_t BinaryHeap<T>::size() {
        return size_;
    }

    template<typename T>
    bool BinaryHeap<T>::empty() {
        return empty_;
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

    template<typename T>
    size_t BinaryHeap<T>::parent(size_t child) {

        if (child <= 2) return 0;

        return (child - 1) / 2;

    }

}

#endif //CPPREF_BINARYHEAP_IMPL_H
