#include "test_rule_of_X.h"

void test_rule_of_X() {
    using rule_of_X::Q;

    Q q1;
    Q& q1point5 = *new Q();
    Q q2((int)q1);
    Q q3 = q2;
    Q q4 = std::move(q3);

    {
        Q q5;
        q5 = q4; // copy assign
        Q q6;
        console_test(0, results.dtor_count);
        q6 = 5 + (int) q5; // move assign, the Q rval cast from 5 was destroyed in the same line
        console_test(1, results.dtor_count);
        console_test(q5.state, Q::assign_copy);
        console_test(q6.state, Q::assign_move);
    } // q5, q6 destroyed

    console_test(3, results.dtor_count); // tricky 3rd destructor call!
    console_test(q1point5.state, Q::ctor);
    console_test(q1.state, Q::ctor);
    console_test(q2.state, Q::ctor_param);
    console_test(q3.state, Q::ctor_copy);
    console_test(q4.state, Q::ctor_move);

    // X is apparently 5 or 6
    cout << endl;
}