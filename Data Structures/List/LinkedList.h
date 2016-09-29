#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include "List.h"
#include <string>
using std::function;

namespace Lehr {

    /**
     * See List for interface comments.
     */
    template <typename T>
    class LinkedList : public List<T> {
    public:
        typedef T value_type;
        size_t size() override;

        LinkedList<T>();
        LinkedList<T>(T item);
        LinkedList<T>(const LinkedList<T>& copy);
        LinkedList<T>(std::initializer_list<T> list) {
            for (auto i : list) {
                push(i);
            }
        }
        ~LinkedList<T>() override;

        T& operator [](size_t i) override;

        LinkedList<T>* push(T item) override;
        LinkedList<T>* unshift(T item) override;

        void pop() override;
        void shift() override;
        void pop(T& into) override;
        void shift(T& into) override;
        using List<T>::operator >>;
        using List<T>::operator <<;

        int index(const T& item) override;
        bool contains(const T& item) override;

        /**
         * Mutation methods.
         * Excise removes elements, splice inserts elements, slice takes a sub-list.
         */
        LinkedList<T>* sort() override;
        using List<T>::mergesort;
        friend struct Merge<T>;
        LinkedList<T>* excise(int at);
        LinkedList<T>* excise(int from, int to);
        LinkedList<T>* splice(int before, LinkedList<T>& list);
        LinkedList<T>* splice(int before, T& item);
        LinkedList<T>* slice(int index);
        LinkedList<T>* slice(int index, int length);
        LinkedList<T>* map(function<T(T)> fn);
        LinkedList<T>* filter(function<bool(T)> fn);

        void clear() override {
            while (size() > 0) {
                pop();
            }
        }

        struct iterator;
        iterator begin();
        iterator end();

    protected:
        using List<T>::sortable;
        size_t length = 0;
        struct Node {
            friend class LinkedList<T>;
            T item;
            Node* next = nullptr;
            Node() {};
            Node(T item) : item(item) {};
            Node(Node* next) : next(next) {};
            Node(T item, Node* next) : item(item), next(next) {};
            Node(Node* next, T item) : item(item), next(next) {};
            void operator =(T item) {
                this->item = item;
            };
        };
        Node* head = nullptr;
        Node* tail = nullptr;
        Node* node_at(long int i);
    public:
        struct iterator {
            friend class LinkedList<T>;
            friend class Node;

            T& operator ->() {
                return operator *();
            }
            T& operator *() {
                return cursor->item;
            }
            bool operator ==(iterator& right) {
                if (index == end || right.index == end) {
                    return right.index == index;
                }
                return operator *() == *right;
            }
            bool operator !=(iterator& right) {
                return !operator ==(right);
            }
            iterator& operator ++() {
                if (index != end) {
                    if (cursor->next != nullptr) {
                        cursor = cursor->next;
                        index++;
                    } else {
                        index = end;
                        cursor = nullptr;
                    }
                }
                return *this;
            }
            iterator& operator --() {
                if (index == end) {
                    cursor = list.tail;
                } else {
                    if (index > 0) {
                        index--;
                        cursor = list.node_at(index);
                    } else {
                        index = end;
                    }
                }
                return *this;
            }
        protected:
            iterator(Node& node, size_t from_index, LinkedList<T>& list): index(from_index), list(list) {
                cursor = &node;
            }
            iterator(LinkedList<T>& list): list(list) {
                index = end;
                cursor = nullptr;
            }
            const long int end = -1;
            Node* cursor;
            long int index;
            LinkedList<T>&list;
        };
    };

    template class LinkedList<std::string>;
    template class LinkedList<int>;
    template class LinkedList<double>;
}

namespace Lehr {
    template<typename T>
    struct Merge {
        static LinkedList<T>* sort(LinkedList<T>& list, false_type) {
            return &list;
        }
        static LinkedList<T>* sort(LinkedList<T>& list, true_type) {
            size_t middle = list.length / 2;
            LinkedList<T> merge_staging;
            list.mergesort(0, middle, merge_staging);
            return &list;
        }
    };
}

namespace Lehr {
    template <typename T>
    size_t LinkedList<T>::size() {
        return length;
    }
    template <typename T>
    LinkedList<T>::LinkedList() {
    }
    template <typename T>
    LinkedList<T>::LinkedList(T item) {
        length = 1;
        head = new LinkedList<T>::Node(item);
        tail = head;
    }
    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& source) {
        LinkedList<T>::Node* cursor = source.head;
        while (nullptr != cursor) {
            push(cursor->item);
            cursor = cursor->next;
        }
    }
    template <typename T>
    LinkedList<T>::~LinkedList() {
        Node* cursor = head;
        while (nullptr != cursor) {
            Node* deletion = cursor;
            cursor = cursor->next;
            delete deletion;
        }
    }

    template <typename T>
    T& LinkedList<T>::operator [](size_t i) {
        LinkedList<T>::Node* cursor = this->head;
        while ((nullptr != cursor->next) && (i > 0)) {
            cursor = cursor->next;
            i--;
        }
        return cursor->item;
    }

    template <typename T>
    typename LinkedList<T>::Node* LinkedList<T>::node_at(long int i) {
        LinkedList<T>::Node* cursor = this->head;
        while (nullptr != cursor->next && i--) {
            cursor = cursor->next;
        }
        if (i > 0) {
            cursor = nullptr;
        }
        return cursor;
    }

    template <typename T>
    LinkedList<T>* LinkedList<T>::push(T item) {
        LinkedList<T>::Node* node = new LinkedList<T>::Node(item);
        if (nullptr != tail) {
            tail->next = node;
            tail = tail->next;
        } else {
            head = node;
            tail = node;
        }
        length++;
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::unshift(T item) {
        LinkedList<T>::Node* node = new LinkedList<T>::Node(item);
        if (nullptr != head) {
            node->next = head;
        } else {
            tail = node;
        }
        head = node;
        length++;
        return this;
    }

    template <typename T>
    void LinkedList<T>::pop() {
        if (length <= 0) {
            length = 0;
            tail = nullptr;
            head = nullptr;
        } else {
            delete tail;
            if (length > 1) {
                LinkedList<T>::Node* new_tail = node_at((int)length - 2);
                new_tail->next = nullptr;
                tail = new_tail;
            } else if (length == 1) {
                tail = nullptr;
                head = nullptr;
            }
            length--;
        }
    }
    template <typename T>
    void LinkedList<T>::shift() {
        if (length <= 0) {
            length = 0;
            tail = nullptr;
            head = nullptr;
        } else {
            if (length == 1) {
                tail = nullptr;
                delete head;
                head = nullptr;
            } else {
                Node* current_head = head;
                head = current_head->next;
                delete current_head;
            }
            length--;
        }
    }
    template <typename T>
    void LinkedList<T>::pop(T& into) {
        if (length > 0) {
            std::swap(tail->item, into);
            pop();
        }
    }
    template <typename T>
    void LinkedList<T>::shift(T& into) {
        if (length > 0) {
            std::swap(head->item, into);
            shift();
        }
    }
    template <typename T>
    int LinkedList<T>::index(const T& item) {
        Node* cursor = head;
        int index = 0;
        while (nullptr != cursor) {
            if (cursor->item == item) {
                return index;
            }
            index++;
            cursor = cursor->next;
        }
        return -1;
    }
    template <typename T>
    bool LinkedList<T>::contains(const T& item) {
        return index(item) > -1;
    }

    template <typename T>
    LinkedList<T>* LinkedList<T>::sort() {
        typename IsSortable<T>::value_type can_sort;
        return Merge<T>::sort(*this, can_sort);
    }

    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int at) {
        return excise(at, at);
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int from, int to) {
        if (from >= 1) {
            node_at(from - 1)->next = node_at(to + 1);
            length -= to - from + 1;
        } else {
            int n = 0;
            while (n++ <= to) {
                shift();
            }
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::splice(int before, LinkedList<T>& list) {
        size_t original_length = length;
        length += list.length;
        if (before > 0) {
            Node* diverge_at = node_at(before - 1);
            Node* rejoin_at = node_at(before);
            Node* cursor = diverge_at;
            while (list.length) { // todo: way to do this with fewer copies?
                Node* node_copy = new Node();
                list.shift(node_copy->item);
                cursor->next = node_copy;
                cursor = cursor->next;
            }
            cursor->next = rejoin_at;
            if (before >= original_length) {
                tail = cursor;
            }
        } else {
            list.tail->next = head;
            head = list.head;
        }
        LinkedList<T>& examine = *this;
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::splice(int before, T& item) {
        LinkedList<T> container(item);
        return splice(before, container);
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::slice(int index) {
        while (index--) {
            shift();
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::slice(int index, int length) {
        while (index--) {
            shift();
        }
        while (this->length > length) {
            pop();
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::map(function<T(T)> func) {
        for (T& item : *this) {
            item = func(item);
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::filter(function<bool(T)> func) {
        int ix = 0;
        for (T& item : *this) {
            bool keep = func(item);
            if (!keep) {
                excise(ix);
                ix--;
            }
            ix++;
        }
        return this;
    }
    template <typename T>
    typename LinkedList<T>::iterator LinkedList<T>::begin() {
        if (size() > 0) {
            return iterator(*head, 0, *this);
        }
        return end();
    }
    template <typename T>
    typename LinkedList<T>::iterator LinkedList<T>::end() {
        return iterator(*this);
    }
}

#endif //CPPREF_LINKEDLIST_H

