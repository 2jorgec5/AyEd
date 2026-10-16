#include <iostream>

enum Color { RED, BLACK };

template <typename K, typename V>
class RedBlackTree {
private:
    struct Node {
        K key;
        V value;
        Color color = RED;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        Node(K k, V v) : key(k), value(v) {}
    };

    Node* root = nullptr;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* k) {
        Node* uncle;
        while (k->parent && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                uncle = k->parent->parent->right;
                if (uncle && uncle->color == RED) { // Caso 1: Tío ROJO -> Recolorear
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) { // Caso 2: Tío NEGRO (LR)
                        k = k->parent;
                        leftRotate(k);
                    }
                    // Caso 3: Tío NEGRO (LL) -> Rotar y recolorear
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                uncle = k->parent->parent->left;
                if (uncle && uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK; // Regla 2: La raíz siempre es NEGRA
    }

public:
    void insert(K key, V val) {
        Node* node = new Node(key, val);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (node->key < x->key) x = x->left;
            else if (node->key > x->key) x = x->right;
            else { x->value = val; delete node; return; }
        }

        node->parent = y;
        if (!y) root = node;
        else if (node->key < y->key) y->left = node;
        else y->right = node;

        if (!node->parent) {
            node->color = BLACK;
            return;
        }
        if (!node->parent->parent) return;

        fixInsert(node);
    }
};
