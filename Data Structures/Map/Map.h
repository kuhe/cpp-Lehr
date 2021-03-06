#ifndef CPPREF_MAP_H
#define CPPREF_MAP_H

#include "./_map_common.h"

/*
 * This is a hashmap.
 * For an ordered map, see BinarySearchTree in Graph
 */

namespace Lehr {
    /**
     * Act as a Linked-LinkedList like store for hash collisions.
     */
    template <typename K, typename V>
    class KeyValuePair {
    public:
        KeyValuePair() {}
        KeyValuePair(const K& key) : key(key) {
            initialized = true;
        }
        KeyValuePair(const K& key, const V& value) : key(key), value(value) {
            initialized = true;
        }
        K key;
        V value;
        ~KeyValuePair() {
            if (nullptr != next) {
                delete next;
            }
        }
        operator KeyValuePair() {
            return value;
        }
        void operator =(V& value) {
            set_value(value);
        }
        void operator =(V* value) {
            set_value(*value);
        }
        void operator =(V value) {
            set_value(value);
        }
        KeyValuePair* next = nullptr;
        bool is_initialized() {
            return initialized;
        }
        void initialize() {
            initialized = true;
        }
        void deactivate() {
            initialized = false;
        }
    private:
        void set_value(V &value) {
            initialized = true;
            this->value = value;
        }
        bool initialized = false;
    };

    class HashBase {
    public:
        static int hash_string(string key, int size) {
            int h = 0;
            for (char& c : key) {
                h = h << 1 ^ c; // left shift and XOR, if I'm not mistaken
            }
            return h % size;
        }
    };

    template <typename K>
    class Hash {
    public:
        Hash(int size = 128) : size(size) {}
        int operator ()(const K* key) {
            string name;
            const void *address = static_cast<const void *>(key);
            std::stringstream ss;
            ss << address;
            name = ss.str();
            return HashBase::hash_string(name, size);
        }
    private:
        int size;
    };
    template <>
    class Hash<string> {
    public:
        Hash(int size = 128) : size(size) {}
        int operator ()(const string* key) {
            string name = *key;
            return HashBase::hash_string(name, size);
        }
    private:
        int size;
    };
    template <>
    class Hash<int> {
    public:
        Hash(int size = 128) : size(size) {}
        int operator ()(const int* key) {
            string name = std::to_string(*key);
            return HashBase::hash_string(name, size);
        }
    private:
        int size;
    };

    /**
     * Basic dictionary that should allow both read and write with
     * subscript operator. Collisions are chained into a list.
     */
    template <typename K, typename V>
    class Map {
    public:
        Map(int size = 128) : tableSize(size) {
            table = new KeyValuePair<K,V>[tableSize];
        }

        ~Map() {
            delete[] table;
        }

        bool empty() {
            return keys().size() == 0;
        }

        size_t size() {
            return keys().size();
        }

        bool contains(const K& key) {
            int hash_index = hash(&key);
            KeyValuePair<K,V>& bucket = table[hash_index];
            KeyValuePair<K,V>* candidate = &bucket;
            do {
                if (candidate->key == key && candidate->is_initialized()) {
                    return true;
                }
                if (nullptr != candidate->next) {
                    candidate = candidate->next;
                }
            } while(candidate->next != nullptr);
            return candidate->key == key && candidate->is_initialized();
        }

        V& operator [](const K& key) {
            int hash_index = hash(&key);
            KeyValuePair<K,V>& bucket = table[hash_index];
            KeyValuePair<K,V>* candidate = &bucket;

            do {
                if (candidate->key == key) {
                    if (!candidate->is_initialized()) {
                        key_list.push(key);
                        candidate->initialize();
                    }
                    break;
                }
                if (nullptr != candidate->next) {
                    candidate = candidate->next;
                }
            } while(candidate->next != nullptr);

            if (candidate->key != key) {
                if (candidate->is_initialized()) {
                    if (candidate->next == nullptr) {
                        candidate->next = new KeyValuePair<K,V>(key);
                    }
                    candidate = candidate->next;
                } else {
                    candidate->initialize();
                }
                candidate->key = key;
                key_list.push(key);
            }

            return candidate->value;
        }
        int hash(const K& key) const {
            Hash<K> h(tableSize);
            return h(&key);
        }
        int hash(const K* key) const {
            Hash<K> h(tableSize);
            return h(key);
        }
        LinkedList<K> keys() { // copies the keys
            return key_list;
        }

        Map<K, V>* remove(const K& key) {
            return operator -(key);
        };
        Map<K, V>* operator -(const K& key) {
            int hash_index = hash(&key);
            KeyValuePair<K,V>& bucket = table[hash_index];
            KeyValuePair<K,V>* candidate = &bucket;

            while (candidate->next != nullptr && candidate->key != key) {
                candidate = candidate->next;
            }
            if (candidate->key == key) {
                candidate->deactivate();
                key_list.excise(key_list.index(key));
            }

            return this;
        };
    protected:
        LinkedList<K> key_list;
    private:
        int tableSize = 128;
        KeyValuePair<K,V>* table;
    };
}

#endif //CPPREF_MAP_H
