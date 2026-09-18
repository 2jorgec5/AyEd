#include <iostream>
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
    void in_order_recursive(node* current) const {
        if (current == nullptr) return;

        in_order_recursive(current->left);
        cout << current->key << " ";
        in_order_recursive(current->right);
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
        node **current = &root;
        int current_level = 0;
        while (*current != nullptr) {
            if (key == (*current)->key) return false;
            if (key < (*current)->key) {
                current = &((*current)->left);
            } else {
                current = &((*current)->right);
            }
            current_level++;
        }
        *current = new node(key, value, current_level);
        tree_height = max(tree_height, current_level);
        return true;
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
            } else {current = current->right;}
        }
        return -1;
    }

    node* search(const K& target) const {
        return search_recursive(root, target);
    }

    void in_order() const {
        in_order_recursive(root);
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
};
