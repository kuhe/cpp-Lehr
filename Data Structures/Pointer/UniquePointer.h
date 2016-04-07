#ifndef CPPREF_UNIQUE_H
#define CPPREF_UNIQUE_H

#include "_pointer_common.h"

namespace Lehr {

    template<typename T>
    struct UniquePointer {
        UniquePointer();
//        UniquePointer(T& pointee);
        UniquePointer(T* pointer);
        UniquePointer(UniquePointer<T>& other);
        UniquePointer(UniquePointer<T>&& other);
        void operator =(UniquePointer<T>& other);
        void operator =(UniquePointer<T>&& other);
        void operator =(T& item);
        void operator =(T&& item);
        ~UniquePointer();

        bool operator ==(nullptr_t nil);
        bool operator !=(nullptr_t nil);
        bool operator ==(T* ptr);
        bool operator !=(T* ptr);
        bool operator ==(UniquePointer<T>& u_ptr);
        bool operator !=(UniquePointer<T>& u_ptr);

        // would explicit cast to raw ptr be a dangerous method to have?
        T* get();
        T& operator *();
        T* operator ->();

        friend struct SharedPointer<T>;
    protected:
        void take_over(UniquePointer<T>& other);
        void free();
        void release();
    private:
        T* raw_pointer = nullptr;
    };

    // EMC++ Item 21
    template<typename T, typename... R>
    UniquePointer<T> make_unique_pointer(R&&... ctor_args) {
        return UniquePointer<T>(new T(std::forward<R>(ctor_args)...));
    }

}

#include "UniquePointer.impl.h"

#endif //CPPREF_UNIQUE_H
