#ifndef CPPREF_SET_H
#define CPPREF_SET_H

#include <sstream>
#include "_set_common.h"
#include "../Map/_map_common.h"

namespace Lehr {
    using Lehr::Map;
    /**
     * Note: this implementation will be a HashSet
     */
    template <typename T>
    class Set {
        struct Entry;
        Map<T, Entry>* map = new Map<T, Entry>();
    public:
        Set() {
        }
        ~Set() {
            delete map;
        }
        bool operator [](const T& val) {
            return map->operator [](val).is_set;
        }
        bool contains(const T& val) {
            return this->operator [](val);
        };
        bool add(const T& val) {
            bool exists = (bool) map->operator [](val) != unset;
            map->operator [](val).set();
            return exists;
        }
        bool remove(const T& val) {
            bool exists = (bool) map->operator [](val);
            map->operator [](val).unset();
            return exists;
        }
        void clear() {
            delete map;
            map = new Map<T, Entry>();
        }
    private:
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
        char unset = '\0';
    };
}


#endif //CPPREF_SET_H
