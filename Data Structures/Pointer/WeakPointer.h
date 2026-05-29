#ifndef CPPREF_WEAKPOINTER_H
#define CPPREF_WEAKPOINTER_H

#include "_pointer_common.h"

namespace Lehr {

    /**
     * A pointer that will work as long as the shared pointer it is assigned to.
     */
    template<typename T>
    struct WeakPointer {
        WeakPointer() = delete;
        WeakPointer(const WeakPointer<T>& copy) : control(copy.control) {}
        WeakPointer& operator =(const WeakPointer<T>& copy) {
            control = &copy.control;
            return this;
        }
        WeakPointer& operator =(const WeakPointer<T>&& move) {
            control = &move.control;
        }

        WeakPointer(SharedPointer<T>& shared_ptr) : control(shared_ptr.control_block) {
            ++control->weak_references;
        }
        WeakPointer(SharedPointer<T>&& shared_ptr) : control(shared_ptr.control_block) {
            ++control->weak_references;
        }
        WeakPointer& operator =(SharedPointer<T>& shared_ptr) {
            reacquire(shared_ptr);
            return *this;
        }
        WeakPointer& operator =(SharedPointer<T>&& shared_ptr) {
            reacquire(shared_ptr);
            return *this;
        }

        ~WeakPointer() {
            if (control != nullptr) {
                --control->weak_references;
            }
        }
        SharedPointer<T> lock() {
            if (control->references > 0) {
                return SharedPointer<T>(control);
            }
            return SharedPointer<T>();
        }
        T* get() {
            return control->raw_pointer;
        }
        T& operator *() {
            return *get();
        }
        T* operator ->() {
            return get();
        }
        operator T*() {
            return get();
        }
        bool operator ==(nullptr_t nil) {
            return control->references == 0;
        }
        bool operator !=(nullptr_t nil) {
            return !operator ==(nil);
        }
        bool operator ==(T* ptr) {
            return get() == ptr;
        }
        bool operator !=(T* ptr) {
            return get() != ptr;
        }
    private:
        typename SharedPointer<T>::ControlBlock* control = nullptr;

        void reacquire(SharedPointer<T>& shared_ptr) {
            --control->weak_references;
            control = shared_ptr.control_block;
            ++control->weak_references;
        }

    };

}

#endif //CPPREF_WEAKPOINTER_H
