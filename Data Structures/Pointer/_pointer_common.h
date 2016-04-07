#ifndef CPPREF_POINTER_COMMON_H
#define CPPREF_POINTER_COMMON_H

#include <string>
// for std::nullptr_t
using std::nullptr_t;

namespace Lehr {
    template<typename T>
    struct UniquePointer;

    template<typename T>
    struct SharedPointer;
}

#include "UniquePointer.h"
#include "SharedPointer.h"

#endif //CPPREF_POINTER_COMMON_H
