#ifndef CPPREF_ARRAYLIST_H
#define CPPREF_ARRAYLIST_H

#include "List.h"
#include <string>
#include <array>

using std::array;

namespace Lehr {
    template <typename T>
    class ArrayList : public List<T> {
    public:
        typedef T value_type;
        size_t size() override;

        ArrayList<T>();
        ArrayList<T>(T item);
        ArrayList<T>(const ArrayList<T>& copy);
        ArrayList<T>(std::initializer_list<T> list) {
            for (auto i : list) {
                push(i);
            }
        }
        ~ArrayList<T>() override;

        T& operator [](size_t i) override;

        ArrayList<T>* push(T item) override;
        ArrayList<T>* unshift(T item) override;

        void pop() override;
        void shift() override;
        void pop(T& into) override;
        void shift(T& into) override;
        using List<T>::operator >>;
        using List<T>::operator <<;

        int index(const T& item) override;
        bool contains(const T& item) override;

        /**
         * mutation methods
         */
        ArrayList<T>* sort() override;
        using List<T>::mergesort;
        ArrayList<T>* excise(int at);
        ArrayList<T>* excise(int from, int to);
        ArrayList<T>* splice(int before, ArrayList<T>& list);
        ArrayList<T>* splice(int before, T& item);
        ArrayList<T>* slice(int index);
        ArrayList<T>* slice(int index, int length);
        ArrayList<T>* map(function<T(T)> fn);
        ArrayList<T>* filter(function<bool(T)> fn);

        void clear() override;

        struct iterator;
        iterator begin();
        iterator end();

    protected:
        double resize_scalar = 1.5;
        size_t length = 0;
        T* data = nullptr;
        void resize(size_t n, int start_index = 0);
        size_t data_size = 0;
        
    public:
        struct iterator {
            friend class ArrayList<T>;

            T& operator ->() {
                return operator *();
            }
            T& operator *() {
                return list[index];
            }
            bool operator ==(iterator& right) {
                if (index == end) {
                    return right.index == end;
                }
                return operator *() == *right;
            }
            bool operator !=(iterator& right) {
                return !operator ==(right);
            }
            iterator& operator ++() {
                if (index < list.length) {
                    index++;
                } else {
                    index = end;
                }
                return *this;
            }
            iterator& operator --() {
                if (index == end) {
                    index = list.length - 1;
                } else {
                    if (index > 0) {
                        index--;
                    } else {
                        index = end;
                    }
                }
                return *this;
            }
        protected:
            iterator(size_t from_index, ArrayList<T>& list): index(from_index), list(list) {
                if (list.size() == 0) {
                    index = end;
                }
            }
            const long int end = -1;
            long int index;
            ArrayList<T>& list;
        };
    };

    template class ArrayList<std::string>;
    template class ArrayList<int>;
    template class ArrayList<double>;
}

namespace Lehr {
    template <typename T>
    size_t ArrayList<T>::size() {
        return length;
    }
    template <typename T>
    ArrayList<T>::ArrayList() {
        resize(0);
    }
    template <typename T>
    ArrayList<T>::ArrayList(T item) {
        resize(1);
        data[0] = item;
        length = 1;
    }
    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList<T>& source) {
        resize(source.length);
        length = source.length;
        for (int i = 0; i < length; i++) {
            data[i] = source.data[i];
        }
    }
    template <typename T>
    ArrayList<T>::~ArrayList() {
        resize(0);
    }

    template <typename T>
    T& ArrayList<T>::operator [](size_t i) {
        return data[i];
    }

    template <typename T>
    ArrayList<T>* ArrayList<T>::push(T item) {
        if (data_size >= length) {
            resize((size_t) (resize_scalar * (length + 1)));
        }
        data[length] = item;
        length++;
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::unshift(T item) {
        if (data_size >= length + 1) {
            resize((size_t) (resize_scalar * (length + 2)));
        }
        for (size_t i = length; i > 0; i--) {
            data[i] = data[i-1];
        }
        data[0] = item;
        length++;
        return this;
    }
    template <typename T>
    void ArrayList<T>::pop() {
        if (length > 0) {
            length--;
        }
    }
    template <typename T>
    void ArrayList<T>::shift() {
        if (length > 0) {
            resize(length - 1, 1);
        }
    }
    template <typename T>
    void ArrayList<T>::pop(T& into) {
        if (length > 0) {
            size_t index = length - 1;
            //  T copy = data[index];
            // into = copy;
            into = std::move(data[index]);
            length--;
        }
    }
    template <typename T>
    void ArrayList<T>::shift(T& into) {
        if (length > 0) {
            //T copy = data[0];
            //into = copy;
            into = std::move(data[0]);
            resize(length - 1, 1);
        }
    }
    template <typename T>
    int ArrayList<T>::index(const T& item) {
        size_t index = 0;
        T& cursor = this->operator [](index);
        while (index < length) {
            if (this->operator [](index) == item) {
                return index;
            }
            index++;
            cursor = this->operator [](index);
        }
        return -1;
    }
    template <typename T>
    bool ArrayList<T>::contains(const T& item) {
        return index(item) > -1;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::sort() {
        size_t middle = length / 2;
        ArrayList<T> merge_staging;
        mergesort(0, middle, merge_staging);
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::excise(int at) {
        return excise(at, at);
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::excise(int from, int to) {
        if (to < from) return this;
        T empty;
        int offset = to - from + 1;
        for (int i = from; i <= to; i++) {
            data[i] = data[i + offset];
            data[i + offset] = empty;
        }
        length -= offset;
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::splice(int before, ArrayList<T>& list) {
        if (before >= length) {
            for (int i = 0; i < list.length; i++) {
                push(list[i]);
            }
        } else {
            resize(length + list.length);

            // hello how name is
            // hello how ___ ___ __ name is
            //         ^ are you my

            for (int i = before; i < length; i++) {
                data[i + list.length] = data[i];
            }
            for (int j = before; j < before + list.length; j++) {
                data[j] = list[j - before];
            }
            length += list.length;
        }
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::splice(int before, T& item) {
        T copy = item;
        ArrayList<T> container(copy);
        return splice(before, container);
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return this;
    }

    template <typename T>
    void ArrayList<T>::resize(size_t n, int start_index) {
        if (data_size == n && start_index == 0) {
            return;
        }
        data_size = n;
        T* transfer = new T[n];
        for (int i = 0; i + start_index < length && i < n; i++) {
            transfer[i] = data[i + start_index];
        }
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
        if (length > n) {
            length = n;
        } else {
            length -= start_index;
        }
        data = transfer;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::map(function<T(T)> func) {
        for (T& item : *this) {
            item = func(item);
        }
        return this;
    }
    template <typename T>
    ArrayList<T>* ArrayList<T>::filter(function<bool(T)> func) {
        ArrayList<T> temp;
        for (T& item : *this) {
            bool keep = func(item);
            if (keep) {
                temp.push(item);
            }
        }
        resize(0);
        for (auto item : temp) {
            push(item);
        }
        return this;
    }
    template <typename T>
    typename ArrayList<T>::iterator ArrayList<T>::begin() {
        return iterator(0, *this);
    }
    template <typename T>
    typename ArrayList<T>::iterator ArrayList<T>::end() {
        return iterator(length, *this);
    }
    template<typename T>
    void ArrayList<T>::clear() {
        resize(0);
    }
}


#endif //CPPREF_ARRAYLIST_H

