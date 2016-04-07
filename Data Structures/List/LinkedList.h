#ifndef CPPREF_LINKEDLIST_H
#define CPPREF_LINKEDLIST_H

#include "List.h"
#include <string>

namespace Lehr {
    template <typename T>
    class LinkedList : public List<T> {
    public:
        size_t size() override;

        LinkedList<T>();
        LinkedList<T>(T item);
        LinkedList<T>(const LinkedList<T>& copy);
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
        T& begin() override;
        T& end() override;

        int index(const T& item) override;
        bool contains(const T& item) override;

        /**
         * mutation methods
         */
        LinkedList<T>* sort() override;
        using List<T>::mergesort;
        LinkedList<T>* excise(int at);
        LinkedList<T>* excise(int from, int to);
        LinkedList<T>* splice(int before, LinkedList<T>& list);
        LinkedList<T>* splice(int before, T& item);
        LinkedList<T>* slice(int index);
        LinkedList<T>* slice(int index, int length);
    protected:
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
        Node*node_at(int i);
    };

    template class LinkedList<std::string>;
    template class LinkedList<int>;
    template class LinkedList<double>;
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
    typename LinkedList<T>::Node* LinkedList<T>::node_at(int i) {
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
        T copy = item;
        LinkedList<T>::Node* node = new LinkedList<T>::Node(copy);
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
        T dummy;
        pop(dummy);
    }
    template <typename T>
    void LinkedList<T>::shift() {
        T dummy;
        shift(dummy);
    }
    template <typename T>
    void LinkedList<T>::pop(T& into) {
        if (length <= 0) {
            length = 0;
            tail = nullptr;
            head = nullptr;
        } else {
            T copy = tail->item;
            into = copy;
            delete tail;
            if (length > 1) {
                LinkedList<T>::Node* new_tail = node_at(length - 2);
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
    void LinkedList<T>::shift(T& into) {
        if (length <= 0) {
            length = 0;
            tail = nullptr;
            head = nullptr;
        } else {
            T copy = head->item;
            into = copy;
            if (length == 1) {
                tail = nullptr;
                head = nullptr;
                length = 0;
            } else {
                Node* current_head = head;
                head = current_head->next;
                delete current_head;
                length--;
            }
        }
    }
    template <typename T>
    T& LinkedList<T>::begin() {
        return head->item;
    }
    template <typename T>
    T& LinkedList<T>::end() {
        return tail->item;
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
        int middle = length / 2;
        LinkedList<T> merge_staging;
        mergesort(0, middle, merge_staging);
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int at) {
        if (at > 1) {
            node_at(at - 1)->next = node_at(at + 1);
            length--;
        } else {
            shift();
        }
        return this;
    }
    template <typename T>
    LinkedList<T>* LinkedList<T>::excise(int from, int to) {
        if (from > 1) {
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
        int original_length = length;
        length += list.length;
        if (before > 0) {
            Node* diverge_at = node_at(before - 1);
            Node* rejoin_at = node_at(before);
            Node* cursor = diverge_at;
            while (list.length) {
                T new_item;
                list.shift(new_item);
                Node* node_copy = new Node(new_item);
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
}

#endif //CPPREF_LINKEDLIST_H

