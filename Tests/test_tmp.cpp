
#include "test_tmp.h"

namespace LehrTest {
    template<int N>
    struct Factorial {
        static constexpr int value = N * Factorial<N - 1>::value;
    };

    template <>
    struct Factorial<0> {
        static constexpr int value = 1;
    };

    struct true_type {
        static constexpr bool value = true;
    };
    struct false_type {
        static constexpr bool value = false;
    };

    template <typename A, typename B>
    struct is_same : public false_type {};

    template<typename A>
    struct is_same<A, A> : public true_type {};

}

int test_tmp() {

    using LehrTest::Factorial;
    using LehrTest::is_same;

    console_test(Factorial<5>::value, 5 * 4 * 3 * 2);
    console_test(Factorial<10>::value, 5 * 4 * 3 * 2 * 6 * 7 * 8 * 9 * 10);

    using T = int;
    using R = double;

    console_test(is_same<T, T>::value);
    console_test(is_same<R, R>::value);
    console_test(!is_same<R, T>::value);
    console_test(!is_same<T, R>::value);

    cout << endl;

    return 0;

}