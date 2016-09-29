#ifndef CPPREF_LISTINTERFACE_H
#define CPPREF_LISTINTERFACE_H

#include "_list_common.h"

namespace Lehr {
    /**
     * The List api here presents it as a deque, but implementations do not
     * necessarily have equal complexity operating on either end.
     */
    template <typename T>
    class List {
    public:
        virtual size_t size() = 0;
//        virtual List<T>();
//        virtual List<T>(T item);
//        virtual List<T>(const List<T>& copy);
        virtual ~List<T>() {};

        virtual T& operator[](size_t i) = 0;

        /**
         * Inserts a copy of item at the end.
         */
        virtual List<T>* push(T item) = 0;

        /**
         * Inserts a copy of [item] at the beginning.
         */
        virtual List<T>* unshift(T item) = 0;

        /**
         * Remove and delete the last item.
         */
        virtual void pop() = 0;

        /**
         * Remove and delete the first item.
         */
        virtual void shift() = 0;

        /**
         * Uh, should be swapping the last item into the provided reference.
         */
        virtual void pop(T& into) = 0;

        /**
         * Ideally speaking, swaps the first item into the provided reference.
         */
        virtual void shift(T& into) = 0;

        virtual void operator >>(T& into) {
            pop(into);
        }

        virtual void operator <<(T& into) {
            shift(into);
        }

        /**
         * Index of the item or -1, hence the int type. :\.
         */
        virtual int index(const T& item) = 0;

        virtual bool contains(const T& item) = 0;

        /**
         * The comparator is less than. Currently no provision for customization.
         */
        virtual List<T>* sort() = 0;

        /**
         * Empty the list.
         */
        virtual void clear() = 0;

        /**
         * Divide and conquer.
         */
        void mergesort(size_t left, size_t right, List<T>& stage) {
            size_t index = left;
            size_t segment_length = (right - left);
            if (right != left) {
                if (left + 1 != right) {
                    mergesort(left, left + segment_length / 2, stage);
                    stage.clear();
                    mergesort(right, right + segment_length / 2, stage);
                    stage.clear();
                }
            }
            struct Assign {
                static void from_index(List<T>& merge_to, List<T>* list, size_t& cursor) {
                    T val = list->operator[](cursor);
                    merge_to.push(val);
                    cursor++;
                }
            };

            {
                size_t left_limit = left + segment_length;
                size_t right_limit = right + segment_length;

                // merge from the segment provided
                while (left < left_limit || right < right_limit) {
                    if (left >= left_limit) {
                        Assign::from_index(stage, this, right);
                    } else if (right >= right_limit) {
                        Assign::from_index(stage, this, left);
                    } else {
                        if (this->operator[](left) > this->operator[](right)) {
                            Assign::from_index(stage, this, right);
                        } else {
                            Assign::from_index(stage, this, left);
                        }
                    }
                }

                while (stage.size() > 0) {
                    T val;
                    stage.shift(val);
                    this->operator[](index) = val;
                    index++;
                }
            }
        }
    protected:
        static constexpr bool sortable = IsSortable<T>::value;
    };
}

#endif //CPPREF_LISTINTERFACE_H
