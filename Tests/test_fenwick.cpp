#include "test_fenwick.h"

using Lehr::FenwickTree;

int test_fenwick() {

    FenwickTree<int> fw(10000);

    console_test(fw.size() == 10000);

    cout << endl;

    return 0;

}
