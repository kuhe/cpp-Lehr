#ifndef CPPREF_TEST_COMMON_H
#define CPPREF_TEST_COMMON_H

#include "../Utilities/_std_symbols.h"
#include <string>
#include <iostream>

struct Results {
    int score;
    int failed;
    int dtor_count;
};

extern Results results;

template <typename T, typename V>
bool console_test(T a, V b) {
    if (a == b) {
        cout << ".";
        results.score++;
        return true;
    } else {
        results.failed++;
        cout << "\n" << a << " != " << b << endl;
    }
    return false;
}
template <typename T>
bool console_test(T a) {
    if (a) {
        cout << ".";
        results.score++;
    } else {
        results.failed++;
        cout << "\n" << a << " !! " << endl;
    }
    return a;
}
template bool console_test<string, string>(string a, string b);
template bool console_test<int, int>(int a, int b);
template bool console_test<bool, bool>(bool a, bool b);
template bool console_test<double, double>(double a, double b);
template bool console_test<bool>(bool a);

#endif //CPPREF_TEST_COMMON_H
