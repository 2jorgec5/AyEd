//
// Created by Jorge  Cuevas Sánchez  on 9/09/26.
//

#ifndef HASHTABLE_HASH_TABLE_H
#define HASHTABLE_HASH_TABLE_H


#include <iostream>
#include <functional>

template <class K, class V>
class hash_table {
private:
    struct node {
        K key;
        V value;
        node* next;
        node(const K& k, const V& v, node* n = nullptr) : key(k), value(v), next(n) {}
    };

    node** table;
    size_t capacity_;
    size_t size_;

    // Función hash que mapea la clave al tamaño del arreglo
    size_t hash_function(const K& key) const {
        std::hash<K> hash_fn;
        return hash_fn(key) % capacity_;
    }

public:
    // Constructor
    hash_table(size_t cap = 101) : capacity_(cap), size_(0) {
        table = new node*[capacity_](); // Inicializa todos los punteros en nullptr
    }

    // Destructor
    ~hash_table() {
        for (size_t i = 0; i < capacity_; ++i) {
            node* curr = table[i];
            while (curr) {
                node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Insertar o actualizar un valor
    void insert(const K& key, const V& value) {
        size_t index = hash_function(key);
        node** n = &table[index];

        while (*n) {
            if ((*n)->key == key) {
                (*n)->value = value; // Actualiza si la clave ya existe
                return;
            }
            n = &(*n)->next;
        }

        // Inserta al inicio de la lista enlazada en este índice
        table[index] = new node(key, value, table[index]);
        size_++;
    }

    // Buscar un valor por clave
    bool search(const K& key, V& out_value) const {
        size_t index = hash_function(key);
        node* curr = table[index];

        while (curr) {
            if (curr->key == key) {
                out_value = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // Eliminar un nodo
    bool remove(const K& key) {
        size_t index = hash_function(key);
        node** n = &table[index];

        while (*n) {
            if ((*n)->key == key) {
                node* temp = *n;
                *n = temp->next; // El puntero doble salta el nodo
                delete temp;
                size_--;
                return true;
            }
            n = &(*n)->next;
        }
        return false;
    }

  [[nodiscard]]  size_t size() const { return size_; }
  [[nodiscard]]  bool empty() const { return size_ == 0; }
};


#endif //HASHTABLE_HASH_TABLE_H
