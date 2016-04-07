#include "test_const.h"


template<int A, typename T, T B>
class ThingsInLife {
public:
    ThingsInLife() {

    };

    const T sum = template_meta_programming;

    enum states : T {
        caller_const, caller_dynamic, caller_lval, caller_rval, input_const, static_input_const,
        template_meta_programming = A + B
    };

    const T death() const {
        return caller_const;
    }
    const T death() {
        return caller_dynamic;
    }
    static constexpr int death(const int& tax) {
        return static_input_const;
    }

    const T taxes() & {
        return caller_lval;
    }
    const T taxes() && {
        return caller_rval;
    }
    const int taxes(const T& tax) {
        return input_const;
    }

};

template<int I, int I2 = 0>
struct Add {
    static constexpr int val = I;
    const int operator ()(const int other) noexcept {
        return val + other;
    }
    constexpr static int sum = I + I2;
};

int test_const() {

    constexpr int a = 1;
    constexpr int b = 2;
    constexpr int c = a + b;

    Add<1> add;
    constexpr int z = Add<1, 2>::sum;
    const int y = add(2);
    console_test(z, y);

    constexpr int d = c + b;
    const int& e = d + c;
    const int&& f = e + d;

    console_test(f, 13);

    using number_type = u_int8_t;
    using things_in_life_type = ThingsInLife<7, number_type, 9>;
    using s = ThingsInLife<7, number_type, 9>::states;

    things_in_life_type things;
    const things_in_life_type& constants = things;

    console_test(things.taxes(), s::caller_lval);
    console_test(std::move(things).taxes(), s::caller_rval);
    console_test(things.death(), s::caller_dynamic);
    console_test(constants.death(), s::caller_const);
    console_test(things.taxes(100), s::input_const);
    console_test(things_in_life_type::death(100), s::static_input_const);
    console_test(things.sum, s::template_meta_programming);

    cout << endl;
    return 0;
}
