#include "test_map.h"

using Lehr::Map;
using Lehr::LinkedList;
using Lehr::Hash;
using Lehr::KeyValuePair;
using Lehr::Set;

template <typename T, typename V>
void test(T a, V b) {
    console_test(a, b);
}
template void test<string, string>(string a, string b);

struct Thing {
    int value = 0;
    bool operator ==(const Thing& other) {
        return value == other.value;
    }
    bool operator !=(const Thing& other) {
        return value != other.value;
    }
    void operator =(const Thing other) {
    }
    string operator *() {
        return to_string(value);
    }
};

int test_map() {
    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.",
           e = "my.",
           f = "name.",
           g = "is.",
           t1, t2;

    /** test collision */
    Map<string, string> map(1);
    test(map.hash(a), map.hash(a));
    test(map.hash(b), map.hash(b));
    test(map.hash(g), map.hash(g));
    map["greeting"] = "hello";
    map["phrase"] = "how are you";
    map["phrase_two"] = "but I\'m hopin\' all the same";
    t1 = map["greeting"];
    t2 = map["greeting"];
    map["phrase"] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map["phrase"], t2);

    /** test with higher size */
    Map<int, string> map2(128);
    test(map2.hash(1), map2.hash(1));
    test(map2.hash(2), map2.hash(2));
    test(map2.hash(3), map2.hash(3));
    map2[1] = "hello";
    map2[2] = "how are you";
    map2[3] = "but I\'m hopin\' all the same";
    t1 = map2[1];
    t2 = map2[1];
    map2[2] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map2[2], t2);

    /** test with object keys */
    Thing l1, l2, l3;
    Map<Thing, string> map3(1024);
    test(map3.hash(l1), map3.hash(l1));
    test(map3.hash(l2), map3.hash(l2));
    test(map3.hash(l3), map3.hash(l3));
    map3[l1] = "hello";
    map3[l2] = "how are you";
    map3[l3] = "but I\'m hopin\' all the same";
    t1 = map3[l1];
    t2 = map3[l1];
    map3[l2] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map3[l2], t2);

    /** test overloaded hash key */
    Map<int, int> dictionary;
    int k = 1000;
    while (k > 0) {
        dictionary[k] = 3;
        k--;
    }
    dictionary[1001] = 5;
    k = 1000;
    while (k > 0) {
        if (dictionary[k] != 3) {
            test(dictionary[k], 3);
        } else {
            if (k % 100 == 0) {
                test(dictionary[k], 3);
            }
        }
        k--;
    }
    test(dictionary[1001], 5);

    /** test hash set */
    // note: bool keyed map is buggy :(
    Map<int, bool> bMap;
    bMap[0] = true;
    bMap[1] = false;
    test(bMap[0], true);
    test(bMap[1], false);

    bool test1, test2;
    Set<int> s1;
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, false);
    test(test2, false);

    s1.add(false);
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, true);
    test(test2, false);

    s1.add(true);
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, true);
    test(test2, true);

    s1.remove(false);
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, false);
    test(test2, true);

    s1.remove(true);
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, false);
    test(test2, false);

    s1.add(false);
    s1.add(true);
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, true);
    test(test2, true);

    s1.clear();
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, false);
    test(test2, false);

    cout << endl;
    return 0;
};