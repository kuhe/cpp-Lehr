#ifndef CPPREF_SET_H
#define CPPREF_SET_H

#include <sstream>
#include "_set_common.h"
#include "../Map/Map.h"

namespace Lehr {
    using Lehr::Map;
    /**
     * Note: this implementation will be a HashSet
     */
    template <typename T>
    class Set {
        Map<T, bool> map;
    public:
        Set() {
        }
        ~Set() {
        }
        bool operator [](T val) {
            return map[val];
        }
        bool contains(T val) {
            return this->operator [](val);
        };
        bool add(T val) {
            bool exists = map[val];
            map[val] = true;
            return exists;
        }
        bool remove(T val) {
            bool exists = map[val];
            map[val] = false;
            return exists;
        }
        void clear() {
            map = *(new Map<T, bool>);
        }
    };
}


#endif //CPPREF_SET_H
