#ifndef CPPREF_BINARYSEARCHTREE_H
#define CPPREF_BINARYSEARCHTREE_H

#include "./_bst_common.h"

namespace Lehr {

    /**
     * A binary search tree that doesn't know how to balance itself.
     */
    template<typename K, typename V = bool>
    class BinarySearchTree {
    public:

        /**
         *
         */
        BinarySearchTree();

        /**
         * Initialize the root node with a key (value default for that type).
         */
        BinarySearchTree(K key);

        /**
         * Initialize with a root node key value pair.
         */
        BinarySearchTree(K key, V val);

        BinarySearchTree(const BinarySearchTree& model);

        ~BinarySearchTree();

        V& operator [](K key);
        bool contains(K key);
        bool contains_value(V val);

        /**
         * Remove all from the given match down.
         * Note that the value versions of the next few methods will stop at the first value match when walking
         * the tree in order.
         */
        BinarySearchTree* truncate(K key);
        BinarySearchTree* truncate_value(V val);

        /**
         * Remove only the match.
         */
        BinarySearchTree* excise(K key);
        BinarySearchTree* excise_value(V val);

        /**
         * Reform the tree (this) from the subtree starting at the match. Mutates.
         */
        BinarySearchTree* slice(K key);
        BinarySearchTree* slice_value(V val);

        K root_key();

        /**
         * I.e. the height of the tree.
         */
        size_t depth();

        size_t size();

        /**
         * Not yet implemented.
         */
        BinarySearchTree* balance();

        /**
         * (Copy operation)
         */
        ArrayList<K> keys();

        bool empty();

        /**
         * The left-most non-null leaf node.
         */
        V* first() {
            return extremity(false);
        }

        /**
         * The right-most non-null leaf node.
         */
        V* last() {
            return extremity(true);
        }

        /**
         * Naively, iterator instantiation on this type of tree initializes an ArrayList of node pointers.
         */
        struct iterator;

        /**
         * An iterator keyed at the beginning of the list of nodes.
         */
        iterator begin();

        /**
         * An iterator keyed to one past the end of the list of nodes.
         */
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
