#ifndef CPPREF_BINARYSEARCHTREE_H
#define CPPREF_BINARYSEARCHTREE_H

#include "./_bst_common.h"

namespace Lehr {

    template<typename K, typename V = bool>
    class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(K key);
        BinarySearchTree(K key, V val);
        BinarySearchTree(const BinarySearchTree& model);
        ~BinarySearchTree();

        V& operator [](K key);
        bool contains(K key);
        bool contains_value(V val);

        /** remove all from the given match down */
        BinarySearchTree* truncate(K key);
        BinarySearchTree* truncate_value(V val);

        /** remove only the match */
        BinarySearchTree* excise(K key);
        BinarySearchTree* excise_value(V val);

        /** reform from the subtree starting at the match */
        BinarySearchTree* slice(K key);
        BinarySearchTree* slice_value(V val);

        K root_key();
        size_t depth();
        size_t size();
        BinarySearchTree* balance();
        ArrayList<K> keys();
        bool empty();

        V* first() {
            return extremity(false);
        }

        V* last() {
            return extremity(true);
        }

        struct iterator;
        iterator begin();
        iterator end();

    protected:
        V* extremity(bool right) {
            auto cursor = root;
            if (root == nullptr) {
                return nullptr;
            }
            if (right) {
                while (cursor->right != nullptr) {
                    cursor = cursor->right;
                }
            } else {
                while (cursor->left != nullptr) {
                    cursor = cursor->left;
                }
            }
            return &cursor->value;
        }
        struct BSTNode;
        void ingest_copy(BSTNode* node);
        void attach(BSTNode* node);
        void delete_from(BSTNode*& node);
        void delete_only(BSTNode*& node);
        BSTNode* root = nullptr;
        BSTNode*& node_at(K& key);
        BSTNode*& node_at(K& key, BSTNode*& context, BSTNode* parent);
        BSTNode*& node_with(V& val);
        BSTNode*& node_with(V& val, BSTNode*& context, BSTNode* parent);
        V& get(K key);
        V& get(K key, BSTNode*& context, BSTNode* parent = nullptr);
        struct BSTNode {
            friend class BinarySearchTree<K, V>;
            BSTNode(K key): key(key) {};
            BSTNode(K key, V value): key(key), value(value) {};
            BSTNode(K key, V value, BSTNode* parent): key(key), value(value), parent(parent) {};
            BSTNode(K key, V value, BSTNode* left, BSTNode* right):
                    key(key), value(value), left(left), right(right) {};
            BSTNode(K key, V value, BSTNode* parent, BSTNode* left, BSTNode* right):
                    key(key), value(value), parent(parent), left(left), right(right) {};
            BSTNode(const BSTNode& node) {
                parent = node.parent;
                left = node.left;
                right = node.right;
                key = node.key;
                value = node.value;
            }
            explicit operator K*() const { return key; };
            //explicit operator V*() const { return value; };
            K key;
            V value;
            BSTNode* parent = nullptr;
            BSTNode* left = nullptr;
            BSTNode* right = nullptr;
            bool operator ==(BSTNode& other) {
                return other.key == key;
            }
        };

    public:
        struct iterator {
            friend class BinarySearchTree<K, V>;
            friend class BSTNode;

            iterator(BSTNode* from_node): cursor(0) {
                recurse(from_node, 1);
            };

            ArrayList<BSTNode*> members;
            int cursor;
            const int end = -1;
            size_t depth = 0;

            void recurse(BSTNode* node, size_t set_depth) {
                if (nullptr != node) {
                    depth = set_depth;

                    if (nullptr != node->left) {
                        recurse(node->left, set_depth + 1);
                    }
                    members.push(node); // in-order traversal
                    if (nullptr != node->right) {
                        recurse(node->right, set_depth + 1);
                    }
                }
            }
            BSTNode& operator ->() {
                return *members[cursor];
            }
            pair<K, V> operator *() {
                if (cursor == end) {
                    return pair<K, V>();
                }
                auto& ref = (*members[cursor]);
                return pair<K, V&>(ref.key, ref.value);
            }
            bool operator ==(iterator& right) {
                return cursor == right.cursor;
            }
            bool operator !=(iterator& right) {
                return !operator ==(right);
            }
            iterator operator ++() {
                int test1 = cursor;
                long int test2 = members.size() - 1;

                if (cursor >= members.size() - 1) {
                    cursor = end;
                } else {
                    cursor++;
                }
                return *this;
            }
            iterator operator --() {
                if (cursor <= 0) {
                    cursor = end;
                } else {
                    cursor--;
                }
                return *this;
            }
        };
    };

}

#include "BinarySearchTree.impl.h"

#endif //CPPREF_BINARYSEARCHTREE_H
