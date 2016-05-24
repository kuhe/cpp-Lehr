#ifndef CPPREF_SET_H
#define CPPREF_SET_H

#include "_set_common.h"

namespace Lehr {
    template<bool B = false>
    struct Entry;
    /**
     * Note: this implementation will be a HashSet
     */
    template <typename T>
    class Set {
    public:
        Set() {
        }
        ~Set() {
            delete map;
        }
        bool operator [](const T& val) {
            return contains(val);
        }
        bool contains(const T& val) {
            return entry(val).is_set;
        };
        bool add(const T& val) {
            bool exists = contains(val);
            entry(val).set();
            if (!exists) {
                size_internal++;
            }
            return exists;
        }
        bool remove(const T& val) {
            bool exists = contains(val);
            entry(val).unset();
            if (exists) {
                size_internal--;
            }
            return exists;
        }
        void clear() {
            delete map;
            map = new Map<T, Entry<>>();
        }
        LinkedList<T> values() {
            return *map->keys().filter([this](T item) -> bool {
                return contains(item);
            });
        }
        size_t size() {
            return size_internal;
        }
        bool empty() {
            return size() == 0;
        }
    protected:
        size_t size_internal = 0;
        Map<T, Entry<>>* map = new Map<T, Entry<>>();
        Entry<>& entry(const T& val) {
            return (map->operator [](val));
        }
    };

    template <bool B>
    struct Entry {
        explicit operator bool() {
            return is_set;
        }
        bool is_set = B;
        void set() {
            is_set = true;
        }
        void unset() {
            is_set = false;
        }
    };
}

#endif //CPPREF_SET_H
