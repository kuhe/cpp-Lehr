#include "test_threads.h"

/**
 *
 * Contents:
 *
 * Thread - A separate context of linear code execution. When multiple threads run through the same code, the order
 *          of execution is unpredictable.
 *
 * Mutex - Mutual exclusion. An active mutex prohibits other threads from entering its controlled code.
 *      Lock Guard - automatic safe release of a mutex at the end of a scope.
 *      "Counting Semaphore" - https://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 * Atomic - An atomic value is one that, in basic terms, automatically locks during operations on it.
 *
 * In Java:
 * - "synchronized" methods.
 * - atomicity (same concept)
 *
 *
 */
int test_threads() {

#ifdef CPPREF__LEHR_THREADS
    cout << "no threads.. what is this, GCC on windows?";
#endif

#ifndef CPPREF__LEHR_THREADS
#define CPPREF__LEHR_THREADS

    using std::thread;
    using std::move;
    using std::atomic;
    using std::lock_guard;
    using std::mutex;

    /*
     * a - will be freely accessed by multiple threads.
     * b - will be atomic using the standard template.
     * c - will be defended by a mutex.
     */

    int a = 0;
    atomic<int> b;
    b = 0;
    int c = 0;

    mutex m;

    function<void()> increment_c = [&]() -> void {
        lock_guard<mutex> lg(m);
        c++;
    };

    function<void()> decrement_c = [&]() -> void {
        lock_guard<mutex> lg(m);
        c--;
    };

    function<void()> thread1_main = [&]() {
        int n = 9000;
        while (n-- > 0) {
            a++;
            b++;
            increment_c();
        }
    };

    function<void()> thread2_main = [&]() {
        int n = 9000;
        while (n-- > 0) {
            a--;
            b--;
            decrement_c();
        }
    };

    thread t1(thread1_main);
    thread t2(thread2_main);
    thread t3(thread1_main);
    thread t4(thread2_main);

    // thread::join means for the spawned thread to join "this" thread (i.e. the main thread)
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    console_test(a != 0); // though there is a chance a could be 0...
    console_test(b.load(), 0);
    console_test(c, 0);

#endif //CPPREF__LEHR_THREADS

    cout << endl;
    return 0;

};