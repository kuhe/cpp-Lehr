
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
}

int test_tmp() {

    using LehrTest::Factorial;

    console_test(Factorial<5>::value, 5 * 4 * 3 * 2);
    console_test(Factorial<10>::value, 5 * 4 * 3 * 2 * 6 * 7 * 8 * 9 * 10);

    cout << endl;

    return 0;

}