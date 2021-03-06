#include "test_concurrency.h"

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
 * Atomic - An atomic value is one that, in basic terms, automatically locks (*) during operations on it.
 *          (*) Note the locking part is dependent on the type of the atomic value.
 *          Also look into "compare and swap".
 *
 * Future/Promise - Future is readonly whereas Promise is writeable (once), according to wikipedia
 *                  but I'm not clear on what the difference is in C++11 yet.
 *
 * In Java:
 * - "synchronized" methods.
 * - atomicity (same concept)
 * - Future/CompletableFuture
 *
 * In JavaScript:
 * - no multi-threading
 * - Future: Promise with inaccessible resolve function / Promise with accessible resolve function.
 *
 */
int test_concurrency() {

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
    using std::future;
    using std::promise;

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

    function<promise<int>()> thread1_main = [&]() -> promise<int> {
        int n = 9000;
        while (n-- > 0) {
            a++;
        }
        while (n++ < 9000) {
            b++;
            increment_c();
        }
        promise<int> p;
        p.set_value(12345);
        return p;
    };

    function<void()> thread2_main = [&]() {
        int n = 9000;
        while (n-- > 0) {
            a--;
        }
        while (n++ < 9000) {
            b--;
            decrement_c();
        }
    };

    thread t1(thread1_main);
    thread t2(thread2_main);
    thread t3([&]() -> void {
        auto c_promise = thread1_main();
        const int c = c_promise.get_future().get();
        console_test(c, 12345);
    });
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