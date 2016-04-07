#ifndef CPPREF__LIST_COMMON_H
#define CPPREF__LIST_COMMON_H

#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::size_t;

namespace Lehr {
    template <typename T>
    class ArrayList;
    template <typename T>
    class LinkedList;
}

#endif //CPPREF__LIST_COMMON_H
