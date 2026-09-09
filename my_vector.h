//
// Created by User on 8/9/2026.
//

#ifndef MY_VECTOR_MY_VECTOR_H
#define MY_VECTOR_MY_VECTOR_H
#include <iostream>
#include <initializer_list>

template <class T>
class my_vector {
private:
    size_t size_;
    size_t capacity_;
    T* data_;

public:
    // Constructor por defecto
    my_vector() : size_(0), capacity_(1), data_(new T[1]) {}

    // Constructor por initializer_list
    my_vector(std::initializer_list<T> init) : size_(init.size()), capacity_(init.size()) {
        data_ = new T[capacity_];
        size_t i = 0;
        for (const T& val : init) {
            data_[i++] = val;
        }
    }
    // Constructor de copia
    my_vector(const my_vector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    // Operador de asignación
    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    // Destructor
    ~my_vector() {delete[] data_;}

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    void push_back(const T& val) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* new_data = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }

            delete[] data_;
            data_ = new_data;
        }
        data_[size_++] = val;
    }

    // Acceso por indice
    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }

    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
};

#endif //MY_VECTOR_MY_VECTOR_H