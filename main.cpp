#include <iostream>
#include <stdexcept>
#include <iomanip>

template <class T>
class Matrix {
private:
    int rows_;
    int cols_;
    T* data_;

public:
    // 1. Constructor
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        data_ = new T[rows_ * cols_]();
    }

    Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
        data_ = new T[rows_ * cols_];
        for (int i = 0; i < rows_ * cols_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // Operador de asignación
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data_;
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = new T[rows_ * cols_];
            for (int i = 0; i < rows_ * cols_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Matrix() {
        delete[] data_;
    }

    T& operator()(int r, int c) {
        return data_[r * cols_ + c];
    }

    const T& operator()(int r, int c) const {
        return data_[r * cols_ + c];
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i) {
            result.data_[i] = data_[i] - other.data_[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Dimensiones incompatibles");
        }
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                for (int k = 0; k < cols_; ++k) {
                    result(i, j += (*this)(i, k) * other(k, j));
                }
            }
        }
        return result;
    }

    // Método extra para imprimir y verificar
    void print() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << std::setw(4) << (*this)(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Matrix<int> A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Matrix<int> B(2, 2);
    B(0, 0) = 2; B(0, 1) = 0;
    B(1, 0) = 1; B(1, 1) = 2;

    std::cout << "Matriz A:\n"; A.print();
    std::cout << "\nMatriz B:\n"; B.print();

    Matrix<int> C = A + B;
    std::cout << "\nA + B:\n"; C.print();

    Matrix<int> D = A * B;
    std::cout << "\nA * B:\n"; D.print();

    return 0;
}