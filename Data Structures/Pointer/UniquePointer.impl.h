#include "UniquePointer.h"

namespace Lehr {

    template<typename T>
    UniquePointer<T>::UniquePointer() {}
//    template<typename T>
//    UniquePointer<T>::UniquePointer(T& pointee) {
//        raw_pointer = &pointee;
//    }
    template<typename T>
    UniquePointer<T>::UniquePointer(T* pointer) {
        free();
        raw_pointer = pointer;
    };
    template<typename T>
    UniquePointer<T>::UniquePointer(UniquePointer<T>& other) {
        take_over(other);
    };
    template<typename T>
    UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) {
        take_over(other);
    };
    template<typename T>
    void UniquePointer<T>::operator =(UniquePointer<T>& other) {
        take_over(other);
    };
    template<typename T>
    void UniquePointer<T>::operator =(UniquePointer<T>&& other) {
        take_over(other);
    };

    template<typename T>
    void UniquePointer<T>::operator =(T& item) {
        raw_pointer = &item;
    };
    template<typename T>
    void UniquePointer<T>::operator =(T&& item) {
        raw_pointer = &item;
    };

    template<typename T>
    UniquePointer<T>::~UniquePointer() {
        free();
    };
    template<typename T>
    bool UniquePointer<T>::operator ==(nullptr_t nil) {
        return raw_pointer == nil;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(nullptr_t nil) {
        return !operator ==(nil);
    }
    template<typename T>
    bool UniquePointer<T>::operator ==(T* ptr) {
        return raw_pointer == ptr;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(T* ptr) {
        return !operator ==(ptr);
    }
    template<typename T>
    bool UniquePointer<T>::operator ==(UniquePointer<T>& u_ptr) {
        return false;
    }
    template<typename T>
    bool UniquePointer<T>::operator !=(UniquePointer<T>& u_ptr) {
        return true;
    }
    template<typename T>
    T* UniquePointer<T>::get() {
        return raw_pointer;
    }
    template<typename T>
    T& UniquePointer<T>::operator *() {
        return *raw_pointer;
    };
    template<typename T>
    T* UniquePointer<T>::operator ->() {
        return raw_pointer;
    };
    template<typename T>
    void UniquePointer<T>::take_over(UniquePointer<T>& other) {
        raw_pointer = other.raw_pointer;
        other.release();
    }
    template<typename T>
    void UniquePointer<T>::free() {
        if (raw_pointer != nullptr) {
            delete raw_pointer;
            raw_pointer = nullptr;
        }
    }
    template<typename T>
    void UniquePointer<T>::release() {
        raw_pointer = nullptr;
    }

}
