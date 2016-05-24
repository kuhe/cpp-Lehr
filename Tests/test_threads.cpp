#include "test_threads.h"

using std::thread;
using std::move;
using std::atomic;

int test_threads() {

    int a = 0;
    atomic<int> b;
    b = 0;

    function<void()> thread1_main = [&]() {
        int n = INT_MAX/1000;
        while (n-- > 0) {
            a++;
            b++;
        }
    };

    function<void()> thread2_main = [&]() {
        int n = INT_MAX/1000;
        while (n-- > 0) {
            a--;
            b--;
        }
    };

    thread t1(thread1_main);
    thread t2(thread2_main);

    t1.join();
    t2.join();

    console_test(a != 0); // though there is a chance a could be 0...
    console_test(b.load(), 0);

    cout << endl;
    return 0;
};