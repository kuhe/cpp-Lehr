#ifndef CPPREF_WEAKPOINTER_H
#define CPPREF_WEAKPOINTER_H

#include "_pointer_common.h"

namespace Lehr {

    template<typename T>
    struct WeakPointer {
        WeakPointer() = delete;
        WeakPointer(const WeakPointer<T>& copy) : shared(copy.shared) {}
        WeakPointer& operator =(const WeakPointer<T>& copy) {
            shared = &copy.shared;
            return this;
        }
        WeakPointer& operator =(const WeakPointer<T>&& move) {
            shared = &move.shared;
        }

        WeakPointer(SharedPointer<T>& shared_ptr) : shared(&shared_ptr) {
            ++shared->control_block->weak_references;
        }
        WeakPointer(SharedPointer<T>&& shared_ptr) : shared(&shared_ptr) {
            ++shared->control_block->weak_references;
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
            if (shared != nullptr && shared->control_block != nullptr) {
                --shared->control_block->weak_references;
            }
        }
        operator SharedPointer<T>() {
            return *shared;
        }
        SharedPointer<T> get_shared() {
            return *shared;
        }
        T* get() {
            return shared->get();
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
    private:
        SharedPointer<T>* shared = nullptr;

        void reacquire(const SharedPointer<T>& shared_ptr) {
            --shared->control_block->weak_references;
            shared = &shared_ptr;
            ++shared->control_block->weak_references;
        }

    };

}

#endif //CPPREF_WEAKPOINTER_H
