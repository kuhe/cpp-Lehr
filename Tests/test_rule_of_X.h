#ifndef CPPREF_TEST_QUIRKS_H
#define CPPREF_TEST_QUIRKS_H

#include <string>
#include "../Utilities/_std_symbols.h"
#include "./test_common.h"

namespace rule_of_X { // for x = 3, 4, five and a half, etc.

    class Q {
    public:
        Q() {
            state = ctor;
        };
        Q(int data): data(data) {
            state = ctor_param;
        }
        Q(const Q& other) {
            state = ctor_copy;
            data = other.data;
        }
        Q(const Q&& other) {
            state = ctor_move;
            data = other.data;
        }
        void operator =(const Q& other) {
            state = assign_copy;
            data = other.data;
        }
        void operator =(const Q&& other) {
            state = assign_move;
            data = other.data;
        }

        ~Q() {
            results.dtor_count++;
            state = dtor; // well...
        }

        explicit operator int() { // two-way cast operator ??
            return data;
        }

        int data { 0 };
        enum states { ctor, ctor_param, ctor_copy, ctor_move, assign_copy, assign_move, dtor };
        states state {ctor};

        Q& operator +(Q* other) {
            *this = data + (int)*other;
            delete other;
            return *this;
        }
    };
}

void test_rule_of_X();

#endif //CPPREF_TEST_QUIRKS_H
