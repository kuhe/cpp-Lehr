#include "test_fenwick.h"

using Lehr::FenwickTree;

int test_fenwick() {

    FenwickTree<int> fw(10, 0);

    console_test(fw.size() == 10);

    vector<int> example = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (auto i : example) {
        fw.set(i, (size_t) i - 1);
    }

    console_test(fw[0], 1);
    console_test(fw[1], 2);
    console_test(fw[2], 3);
    console_test(fw[3], 4);
    console_test(fw[4], 5);
    console_test(fw[5], 6);
    console_test(fw[6], 7);
    console_test(fw[7], 8);
    console_test(fw[8], 9);
    console_test(fw[9], 10);

    console_test(fw.sum(0, 0), 1);
    console_test(fw.sum(0, 1), 3);
    console_test(fw.sum(0, 2), 6);
    console_test(fw.sum(0, 3), 10);
    console_test(fw.sum(0, 4), 15);
    console_test(fw.sum(0, 5), 21);
    console_test(fw.sum(0, 6), 28);
    console_test(fw.sum(0, 7), 36);
    console_test(fw.sum(0, 8), 45);
    console_test(fw.sum(0, 9), 55);

    console_test(fw.sum(5, 8), 30);
    console_test(fw.sum(4, 7), 26);
    console_test(fw.sum(3, 6), 22);
    console_test(fw.sum(0, 3), 10);

    console_test(fw.sum(4, 9), 45);
    console_test(fw.sum(3, 8), 45 - 6);
    console_test(fw.sum(2, 7), 45 - 6 * 2);
    console_test(fw.sum(1, 6), 45 - 6 * 3);

    for (auto i : example) {
        fw.set(11 - i, (size_t) i - 1);
    }

    for (auto i : example) {
        console_test(fw[i - 1], 11 - i);
    }

    for (size_t i = 0; i < 10 - 3; ++i) {
        size_t j = i + 3;
        size_t expected = 46 - 4 * j;
        console_test(fw.sum(i, j), expected);
    }

    cout << endl;

    return 0;

}
