#ifndef CPPREF_SET_H
#define CPPREF_SET_H

#include "./_set_common.h"

namespace Lehr {
    using Lehr::Map;
    /**
     * Note: this implementation will be a HashSet
     */
    template <typename T>
    class Set {
    protected:
        struct Entry;
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
                _size++;
            }
            return exists;
        }
        bool remove(const T& val) {
            bool exists = contains(val);
            entry(val).unset();
            if (exists) {
                _size--;
            }
            return exists;
        }
        void clear() {
            delete map;
            map = new Map<T, Entry>();
        }
        LinkedList<T> values() {

            auto t1 = map->getKeys();

            return *map->getKeys().filter([this](T item) -> bool {

                auto t2 = contains(item);

                return contains(item);
            });
        }
        size_t size() {
            return _size;
        }
        bool empty() {
            return size() == 0;
        }
    protected:
        Map<T, Entry>* map = new Map<T, Entry>();
        size_t _size = 0;
        struct Entry {
            explicit operator bool() {
                return is_set;
            }
            bool is_set = false;
            void set() {
                is_set = true;
            }
            void unset() {
                is_set = false;
            }
        };
        Entry& entry(const T& val) {
            return (map->operator [](val));
        }
    };
}


#endif //CPPREF_SET_H
