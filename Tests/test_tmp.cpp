
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

    template<int L = INT_MAX, int ...Rs>
    struct Minimum {
        static constexpr int valueR = Minimum<Rs...>::value;
        static constexpr int value = valueR < L ? valueR : L;
    };

    template<>
    struct Minimum<(int) INT_MAX> {
        static constexpr int value = INT_MAX;
    };

}

int test_tmp() {

    using LehrTest::Factorial;
    using LehrTest::is_same;
    using LehrTest::Minimum;

    console_test(Factorial<5>::value, 5 * 4 * 3 * 2);
    console_test(Factorial<10>::value, 5 * 4 * 3 * 2 * 6 * 7 * 8 * 9 * 10);

    using T = int;
    using R = double;

    console_test(is_same<T, T>::value);
    console_test(is_same<R, R>::value);
    console_test(!is_same<R, T>::value);
    console_test(!is_same<T, R>::value);

    console_test(Minimum<1>::value, 1);
    console_test(Minimum<2, 1>::value, 1);
    console_test(Minimum<2, 2>::value, 2);
    console_test(Minimum<2, -2, -2, 5>::value, -2);
    console_test(Minimum<2, 1, 3>::value, 1);
    console_test(Minimum<5, 6, 7, 8, 2, 6, 5, 4>::value, 2);

    cout << endl;

    return 0;

}
