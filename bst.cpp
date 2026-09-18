#include <iostream>
#include <string>

using namespace std;

template <class K, class V>
class BST {
private:
    struct node {
        K key;
        V value;
        int level;
        node * left = nullptr;
        node * right = nullptr;
        node * parent = nullptr;

        node(const K& k, const V& v, int lvl) : key(k), value(v), level(lvl){}
    };

    node * root = nullptr;
    int tree_height = -1;

    void free(node * n) {
        if(n == nullptr) return;
        free(n->left);
        free(n->right);
        delete n;
    }

    node* search_recursive(node* current, const K& target) const {
        if (current == nullptr || current->key == target) {
            return current;
        }

        if (target < current->key) {
            return search_recursive(current->left, target);
        }

        return search_recursive(current->right, target);
    }

    void in_order_recursive_format(node* current, bool& first) const {
        if (current == nullptr) return;

        in_order_recursive_format(current->left, first);

        if (!first) cout << " ";
        cout << current->key;
        first = false;

        in_order_recursive_format(current->right, first);
    }

    void transplant(node* u, node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    node* tree_minimum(node* x) const {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    void pre_order_recursive(node* current) const {
        if (current == nullptr) return;

        cout << current->key << " ";
        pre_order_recursive(current->left);
        pre_order_recursive(current->right);
    }

    void post_order_recursive(node* current) const {
        if (current == nullptr) return;

        post_order_recursive(current->left);
        post_order_recursive(current->right);
        cout << current->key << " ";
    }

public:
    BST() = default;

    ~BST() {
        free(root);
    }

    bool insert(const K& key, const V& value = V()) {
        node *y = nullptr;
        node *x = root;
        int current_level = 0;

        while (x != nullptr) {
            y = x;
            if (key == x->key) return false;
            if (key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
            current_level++;
        }

        node *z = new node(key, value, current_level);
        z->parent = y;

        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        tree_height = max(tree_height, current_level);
        return true;
    }

    void remove(const K& key) {
        node* z = search(key);
        if (z == nullptr) return;

        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } else {
            node* y = tree_minimum(z->right);
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    int height() const {
        return tree_height;
    }

    int level(const K& target) const {
        node* current = root;
        while (current != nullptr) {
            if (current->key == target) {
                return current->level;
            }
            if (target < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return -1;
    }

    node* search(const K& target) const {
        return search_recursive(root, target);
    }

    void in_order() const {
        if (root == nullptr) {
            cout << "VACIO\n";
            return;
        }
        bool first = true;
        in_order_recursive_format(root, first);
        cout << "\n";
    }

    void pre_order() const {
        pre_order_recursive(root);
        cout << "\n";
    }

    void post_order() const {
        post_order_recursive(root);
        cout << "\n";
    }

    bool get_value(const K& target, V& out_value) const {
        node* result = search(target);
        if (result != nullptr) {
            out_value = result->value;
            return true;
        }
        return false;
    }

    void floor_ceiling(const K& target, K& floor_val, K& ceil_val, bool& has_floor, bool& has_ceil) const {
        has_floor = false;
        has_ceil = false;
        node* current = root;

        while (current != nullptr) {
            if (current->key == target) {
                floor_val = current->key;
                ceil_val = current->key;
                has_floor = true;
                has_ceil = true;
                return;
            }
            if (current->key < target) {
                floor_val = current->key;
                has_floor = true;
                current = current->right;
            } else {
                ceil_val = current->key;
                has_ceil = true;
                current = current->left;
            }
        }
    }
};
