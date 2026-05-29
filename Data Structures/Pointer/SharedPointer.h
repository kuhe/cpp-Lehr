#ifndef CPPREF_SHAREDPOINTER_H_H
#define CPPREF_SHAREDPOINTER_H_H

#include "_pointer_common.h"

namespace Lehr {

    /**
     * Reference counting shared pointer. The control block preference is on the right side of assignment.
     */
    template<typename T>
    struct SharedPointer {
        // rule of approximately 5
        SharedPointer() {
            initialize_control();
        };
        SharedPointer(T* pointer) {
            initialize_control();
            control_block->raw_pointer = pointer;
            control_block->references = 1;
        };
        SharedPointer(SharedPointer<T>& other) {
            join(other);
        };
        SharedPointer(SharedPointer<T>&& other) {
            control_block = other.control_block;
            other.control_block = nullptr;
        };
        void operator =(SharedPointer<T>& other) {
            join(other);
        };
        void operator =(SharedPointer<T>&& other) {
            free();
            control_block = other.control_block;
            other.control_block = nullptr;
        };

        SharedPointer(UniquePointer<T>& other) {
            take_unique(other);
        };
        SharedPointer(UniquePointer<T>&& other) {
            take_unique(other);
        };
        void operator =(UniquePointer<T>& other) {
            take_unique(other);
        };
        void operator =(UniquePointer<T>&& other) {
            take_unique(other);
        };

        ~SharedPointer() {
            free();
        }

        // other methods
        bool operator ==(nullptr_t nil) {
            return control_block->raw_pointer == nullptr;
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
        bool operator ==(SharedPointer<T>& shared_ptr) {
            return operator ==(shared_ptr.control_block->raw_pointer);
        }
        bool operator !=(SharedPointer<T>& shared_ptr) {
            return operator !=(shared_ptr.control_block->raw_pointer);
        }

        unsigned long int count() {
            return control_block->references;
        }

        unsigned long int weak_count() {
            return control_block->weak_references;
        }

        T* get() {
            return control_block->raw_pointer;
        }
        T& operator *() {
            return *control_block->raw_pointer;
        }
        T* operator ->() {
            return control_block->raw_pointer;
        }
    protected:
        struct ControlBlock {
            friend struct SharedPointer<T>;
            ControlBlock() {}
            T* raw_pointer = nullptr;
            unsigned long int references = 0;
            unsigned long int weak_references = 0;
        };
        SharedPointer(ControlBlock* cb) : control_block(cb) {
            ++control_block->references;
        }
        void initialize_control() {
            if (control_block == nullptr) {
                control_block = new ControlBlock();
            }
        }
        void join(SharedPointer<T>& other) {
            // release own control block.
            free();

            // take on other's control block.
            control_block = other.control_block;
            ++other.control_block->references;
            control_block->raw_pointer = other.control_block->raw_pointer;
        }
        void take_unique(UniquePointer<T>& other) {
            control_block->raw_pointer = other.raw_pointer;
            other.release();
            control_block->references++;
        }
        void free() {
            if (control_block == nullptr) {
                return;
            }
            if (control_block->references > 0) {
                --control_block->references;
            }
            if (control_block->raw_pointer != nullptr) {
                if (control_block->references == 0) {
                    delete control_block->raw_pointer;
                    control_block->raw_pointer = nullptr;

                    if (control_block->weak_references == 0) {
                        delete control_block;
                        control_block = nullptr;
                    }
                }
            }
        }
    private:
        friend struct WeakPointer<T>;
        ControlBlock* control_block = nullptr;
    };

    // emo C++ Item 21
    template<typename T, typename ...R>
    SharedPointer<T> make_shared_pointer(R&&... ctor_args) {
        return SharedPointer<T>(new T(std::forward<R>(ctor_args)...));
    }

}

#endif //CPPREF_SHAREDPOINTER_H_H
