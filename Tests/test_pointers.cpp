#include "test_pointers.h"
#include <map>
#include <unordered_map>

using std::unordered_map;
using std::map;

int test_pointers() {

    struct Widget {
        int id;
        Widget(int i): id(i) {}
        Widget(const Widget& copy) : id(copy.id) {}
    };

    using Lehr::UniquePointer;
    using Lehr::WeakPointer;
    using Lehr::make_unique_pointer;

    UniquePointer<Widget> u_ptr;
    UniquePointer<Widget> u_ptr2;
    UniquePointer<Widget> u_ptr3;

    Widget* volunteer = nullptr;
    Widget* volunteer2 = nullptr;
    Widget* volunteer3 = nullptr;
    {
        Widget stack_widget(10);
        volunteer = &stack_widget;
        {
            volunteer2 = new Widget(2);
            u_ptr3 = volunteer2;
            u_ptr2 = u_ptr3;
            u_ptr = u_ptr2;
            console_test(u_ptr2 == nullptr);
            console_test(u_ptr3 == nullptr);
            console_test(u_ptr->id, 2);
        }
        {
            volunteer3 = new Widget(3);
            u_ptr = nullptr;
            u_ptr = volunteer;
            u_ptr = volunteer3;
            u_ptr2 = volunteer;
            console_test(u_ptr2->id, 10);
            console_test(u_ptr->id, 3);
        }
        u_ptr2 = make_unique_pointer<Widget>(-10);
    }

    console_test(u_ptr->id, 3);
    console_test(u_ptr2->id, -10);
    console_test(u_ptr3 == nullptr);


    using Lehr::SharedPointer;
    using Lehr::make_shared_pointer;

    SharedPointer<Widget> share_ptr1, share_ptr2, share_ptr3;

    {
        auto made = make_shared_pointer<Widget>(15);

        share_ptr1 = made;
        share_ptr2 = share_ptr1;

        console_test(share_ptr1->id, 15);
        console_test(share_ptr2->id, 15);
        console_test(share_ptr2 == share_ptr1);

        console_test(share_ptr1.count(), 3);
    }
    share_ptr3 = u_ptr;

    console_test(u_ptr == nullptr);
    console_test(share_ptr3->id, 3);
    console_test(share_ptr1->id, 15);
    console_test(share_ptr2->id, 15);
    console_test(share_ptr1.count(), 2); // [made] destroyed in the stack frame above, leaving ptr1 and ptr2

    {
        WeakPointer<Widget> weak_ptr1 = share_ptr1;
        WeakPointer<Widget> weak_ptr2 = share_ptr2;
        WeakPointer<Widget> weak_ptr3 = share_ptr2;

        console_test(share_ptr2.weak_count(), 3); // share2 is connected with share1
        {
            console_test(share_ptr1.count(), 2);
            SharedPointer<Widget> temp = weak_ptr1.lock(); // doesn't create a new shared pointer?
            SharedPointer<Widget> temp2 = weak_ptr1.lock();
            SharedPointer<Widget> temp3 = weak_ptr1.lock();
            console_test(share_ptr1.count(), 5);

            console_test(temp->id, 15);
            console_test(weak_ptr3->id, 15);

            // temporary shared pointers destroyed
        }
        console_test(share_ptr2.weak_count(), 3);
        console_test(share_ptr1.count(), 2);

        // weak pointers destroyed
    }

    console_test(share_ptr2.weak_count(), 0);
    console_test(share_ptr1.count(), 2);

    {
        { // null shared pointer test
            SharedPointer <Widget> sp;
            console_test(sp == nullptr);
            WeakPointer <Widget> wp = sp;

            console_test(sp.count(), 0); // shared pointer is null
            console_test(sp.weak_count(), 1);
            console_test(wp == nullptr);
        }

        SharedPointer<Widget> sp = make_shared_pointer<Widget>(16); // precedence is given to RHS control block
        WeakPointer <Widget> wp = sp;

        console_test(sp.count(), 1);
        console_test(sp.weak_count(), 1);
        console_test(sp->id, 16);
        console_test(wp != nullptr);
        console_test(wp->id, 16);

        {
            SharedPointer<Widget> temp = make_shared_pointer<Widget>(35);

            {
                SharedPointer<Widget> sp2 = make_shared_pointer<Widget>(12);
                console_test(sp2.weak_count(), 0);
                console_test(sp2.count(), 1); // shared pointer is initialized
                console_test(sp.weak_count(), 1);
                console_test(sp2->id, 12);

                // reassign wp to sp2

                console_test(wp.lock() == sp);
                console_test(wp.lock() != sp2);
                wp = sp2;
                console_test(wp.lock() != sp);
                console_test(wp.lock() == sp2);

                console_test(sp2.count(), 1);
                temp = wp.lock(); // new shared widget created from sp2
                console_test(temp.count(), 2);
                console_test(sp.weak_count(), 0);
                console_test(sp2.count(), 2);
                console_test(sp2->id, 12);
                console_test(wp != nullptr);
                // sp2 deallocates
            }

            console_test(temp.count(), 1); // temp remains as only holder of what sp2 held
            console_test(temp.weak_count(), 1);
            console_test(temp->id, 12);

            console_test(sp.weak_count(), 0);
            console_test(sp.count(), 1);
            console_test(wp.lock()->id, 12);
            console_test(wp->id, 12);

            console_test(wp.lock().count(), 2); // 2 because lock was called twice

            // temp deallocates, weak pointer should now be back to null
        }

        console_test(wp == nullptr);

    }

    cout << endl;
    return 0;
};
