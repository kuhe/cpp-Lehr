#ifndef CPPREF_SHAREDPOINTER_H_H
#define CPPREF_SHAREDPOINTER_H_H

#include "_pointer_common.h"

namespace Lehr {

    template<typename T>
    struct SharedPointer {
        // rule of approximately 5
        SharedPointer() {
            initialize_control();
        };
        SharedPointer(T* pointer) {
            initialize_control();
            raw_pointer = pointer;
            control_block->references = 1;
        };
        SharedPointer(SharedPointer<T>& other) {
            join(other);
        };
        SharedPointer(SharedPointer<T>&& other) {
            join(other);
        };
        void operator =(SharedPointer<T>& other) {
            join(other);
        };
        void operator =(SharedPointer<T>&& other) {
            join(other);
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

        void operator =(T& item) {
            initialize_control();
            control_block->references = 1;
            raw_pointer = &item;
        }
        void operator =(T&& item) {
            initialize_control();
            control_block->references = 1;
            raw_pointer = &item;
        }
        ~SharedPointer() {
            if (--control_block->references == 0) {
                free();
            }
        }

        // other methods
        bool operator ==(nullptr_t nil) {
            return raw_pointer == nullptr;
        }
        bool operator !=(nullptr_t nil) {
            return !operator ==(nil);
        }
        bool operator ==(T* ptr) {
            return raw_pointer == ptr;
        }
        bool operator !=(T* ptr) {
            return !operator !=(ptr);
        }
        bool operator ==(SharedPointer<T>& shared_ptr) {
            return operator ==(shared_ptr.raw_pointer);
        }
        bool operator !=(SharedPointer<T>& shared_ptr) {
            return operator !=(shared_ptr.raw_pointer);
        }

        unsigned long int count() {
            if (control_block == nullptr) {
                return 0;
            }
            return control_block->references;
        }
        T* get() {
            return raw_pointer;
        }
        T& operator *() {
            return *raw_pointer;
        }
        T* operator ->() {
            return raw_pointer;
        }
    protected:
        struct ControlBlock {
            friend struct SharedPointer<T>;
            ControlBlock() {}
            unsigned long int references = 0;
            unsigned long int weak_references = 0;
        };
        void initialize_control() {
            if (control_block == nullptr) {
                control_block = new ControlBlock();
            }
        }
        void join(SharedPointer<T>& other) {
            other.control_block->references++;
            control_block = other.control_block;
            raw_pointer = other.raw_pointer;
        }
        void take_unique(UniquePointer<T>& other) {
            raw_pointer = other.raw_pointer;
            other.release();
            control_block->references++;
        }
        void free() {
            if (raw_pointer != nullptr) {
                delete raw_pointer;
                raw_pointer = nullptr;
            }
            if (control_block != nullptr) {
                delete control_block;
                control_block = nullptr;
            }
        }
    private:
        T* raw_pointer = nullptr;
        ControlBlock* control_block = nullptr;
    };

    // EMC++ Item 21
    template<typename T, typename... R>
    SharedPointer<T> make_shared_pointer(R&&... ctor_args) {
        return SharedPointer<T>(new T(std::forward<R>(ctor_args)...));
    }

}

#endif //CPPREF_SHAREDPOINTER_H_H
