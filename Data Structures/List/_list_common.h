#ifndef CPPREF__LIST_COMMON_H
#define CPPREF__LIST_COMMON_H

#include <memory>
#include "../../Utilities/_std_symbols.h"

namespace Lehr {

    struct Unimplemented {};
    template<typename T, typename R>
    Unimplemented operator <(const T&, const R&);

    template<typename T, typename R = T>
    struct IsSortable {
        enum {
            value =
                is_same<T, int>::value ||
                is_same<T, double>::value ||
                false
                // todo check for implementation of comparison operator(s)
                //is_same<decltype(  *(T*)(0) == *(R*)(0)  ), Unimplemented>::value
        };
        typedef integral_constant<bool, value> value_type;
    };

    template<typename T>
    struct Merge;
    template <typename T>
    class ArrayList;
    template <typename T>
    class LinkedList;
}

#include "List.h"

#endif //CPPREF__LIST_COMMON_H
