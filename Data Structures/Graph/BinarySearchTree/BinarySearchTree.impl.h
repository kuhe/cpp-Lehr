#ifndef CPPREF_BINARYSEARCHTREE_CPP_H
#define CPPREF_BINARYSEARCHTREE_CPP_H

#include "./BinarySearchTree.h"

namespace Lehr {

    /**
     * todo: Should be self-balancing
     */
    template<typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree() {};

    template<typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree(K key) {
        root = new BSTNode(key);
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree(K key, V val) {
        root = new BSTNode(key, val);
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree(const BinarySearchTree& model) {
        ingest_copy(model.root);
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>::~BinarySearchTree() {
        delete_from(root);
    }



    template<typename K, typename V>
    V& BinarySearchTree<K, V>::operator [](K key) {
        return get(key);
    }
    template<typename K, typename V>
    bool BinarySearchTree<K, V>::contains(K key) {
        return node_at(key) != nullptr;
    }
    template<typename K, typename V>
    bool BinarySearchTree<K, V>::contains_value(V val) {
        return node_with(val) != nullptr;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::truncate(K key) {
        delete_from(node_at(key));
        return this;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::truncate_value(V val) {
        delete_from(node_with(val));
        return this;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::excise(K key) {
        delete_only(node_at(key));
        return this;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::excise_value(V val) {
        delete_only(node_with(val));
        return this;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::slice(K key) {
        BinarySearchTree<K, V> copy;
        copy.ingest_copy(node_at(key));
        delete_from(root);
        ingest_copy(copy.root);
        return this;
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::slice_value(V val) {
        BinarySearchTree<K, V> copy;
        copy.ingest_copy(node_with(val));
        delete_from(root);
        ingest_copy(copy.root);
        return this;
    }
    template<typename K, typename V>
    K BinarySearchTree<K, V>::root_key() {
        return root->key;
    }
    template<typename K, typename V>
    size_t BinarySearchTree<K, V>::depth() {
        return this->begin().depth; // todo expensive
    }
    template<typename K, typename V>
    size_t BinarySearchTree<K, V>::size() {
        return this->begin().members.size(); // todo expensive
    }
    template<typename K, typename V>
    BinarySearchTree<K, V>* BinarySearchTree<K, V>::balance() {
        // todo
        return this;
    }
    template<typename K, typename V>
    ArrayList<K> BinarySearchTree<K, V>::keys() {
        ArrayList<K> keys;

        for (auto i : *this) { // todo expensive
            keys.push(i.first);
        }

        return keys;
    }

    template<typename K, typename V>
    typename BinarySearchTree<K, V>::iterator BinarySearchTree<K, V>::begin() {
        return iterator(root);
    }
    template<typename K, typename V>
    typename BinarySearchTree<K, V>::iterator BinarySearchTree<K, V>::end() {
        iterator iterator1 = iterator(root);
        iterator1.cursor = iterator1.end;
        return iterator1;
    }

    template<typename K, typename V>
    void BinarySearchTree<K, V>::ingest_copy(BSTNode* node) {
        if (nullptr != node) {
            get(node->key) = node->value;
            if (nullptr != node->left) {
                ingest_copy(node->left);
            }
            if (nullptr != node->right) {
                ingest_copy(node->right);
            }
        }
    }
    template<typename K, typename V>
    void BinarySearchTree<K, V>::attach(BSTNode* node) {
        if (nullptr != node) {
            node_at(node->key) = node;
        }
    }
    template<typename K, typename V>
    void BinarySearchTree<K, V>::delete_from(BSTNode*& node) {
        if (nullptr != node) {
            if (nullptr != node->left) {
                delete_from(node->left);
            }
            if (nullptr != node->left) {
                delete_from(node->left);
            }
            delete node;
            node = nullptr;
        }
    }
    template<typename K, typename V>
    void BinarySearchTree<K, V>::delete_only(BSTNode*& node) {
        if (nullptr != node) {
            BSTNode* left = node->left;
            BSTNode* right = node->right;
            delete node;
            node = nullptr;
            attach(left);
            attach(right);
        }
    }
    template<typename K, typename V>
    typename BinarySearchTree<K, V>::BSTNode*& BinarySearchTree<K, V>::node_at(K& key) {
        return node_at(key, root, nullptr);
    }
    template<typename K, typename V>
    typename BinarySearchTree<K, V>::BSTNode*& BinarySearchTree<K, V>::node_at(K& key, BSTNode*& context, BSTNode* parent) {
        if (nullptr == context) {

        } else {
            if (context->key > key) {
                return node_at(key, context->left, context);
            } else if (context->key < key) {
                return node_at(key, context->right, context);
            }
        }
        return context;
    }
    template<typename K, typename V>
    typename BinarySearchTree<K, V>::BSTNode*& BinarySearchTree<K, V>::node_with(V& val) {
        return node_with(val, root, nullptr);
    }
    template<typename K, typename V>
    typename BinarySearchTree<K, V>::BSTNode*& BinarySearchTree<K, V>::node_with(V& val, BSTNode*& context, BSTNode* parent) {
        if (nullptr == context) {

        } else {
            if (context->value > val) {
                return node_with(val, context->left, context);
            } else if (context->value < val) {
                return node_with(val, context->right, context);
            }
        }
        return context;
    }
    template<typename K, typename V>
    V& BinarySearchTree<K, V>::get(K key) {
        return get(key, root, nullptr);
    }
    template<typename K, typename V>
    V& BinarySearchTree<K, V>::get(K key, BSTNode*& context, BSTNode* parent) {
        if (nullptr == context) {
            context = new BSTNode(key);
            context->parent = parent;
        } else {
            if (context->key > key) {
                return get(key, context->left, context);
            } else if (context->key < key) {
                return get(key, context->right, context);
            }
        }
        return context->value;
    }

}

#endif //CPPREF_BINARYSEARCHTREE_CPP_H
