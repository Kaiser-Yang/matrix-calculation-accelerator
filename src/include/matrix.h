#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <memory>

template <class ELEMENT_TYPE>
class Matrix {
   public:
    struct Shape {
        int rows, columns;
    };

    Matrix() = default;

    Matrix(const Shape &shape, const ELEMENT_TYPE &default_value) {
        this->shape = shape;
        if (shape.rows * shape.columns != 0) {
            data = new ELEMENT_TYPE[shape.rows * shape.columns];
            std::fill(data, data + shape.rows * shape.columns, default_value);
        } else {
            data = nullptr;
        }
    }

    Matrix(const Matrix &other) : data(other.data) {}

    Matrix(Matrix &&other) noexcept : data(std::move(other.data)) {}

    Matrix &operator=(const Matrix &other) {
        shape = other.shape;
        if (shape.rows * shape.columns != 0) {
            data = new ELEMENT_TYPE[shape.rows * shape.columns];
            memcpy(data, other.data, shape.rows * shape.columns * sizeof(ELEMENT_TYPE));
        } else {
            data = nullptr;
        }
    }

    Matrix &operator=(Matrix &&other) noexcept {
        shape = std::move(other.shape);
        data  = std::move(other.data);
    }

    friend bool operator==(const Matrix &a, const Matrix &b);
    friend bool operator!=(const Matrix &a, const Matrix &b);
    friend bool operator<(const Matrix &a, const Matrix &b);
    friend bool operator<=(const Matrix &a, const Matrix &b);
    friend bool operator>(const Matrix &a, const Matrix &b);
    friend bool operator>=(const Matrix &a, const Matrix &b);

    friend Matrix operator+(const Matrix &a, const Matrix &b);
    friend Matrix operator-(const Matrix &a, const Matrix &b);
    friend Matrix operator*(const Matrix &a, const Matrix &b);

    template <class Number>
    friend Matrix operator*(const Matrix &a, const Number &number);
    template <class Number>
    friend Matrix operator*(const Number &number, const Matrix &a);
    template <class Number>
    friend Matrix operator/(const Matrix &a, const Number &number);
    template <class Number>
    friend Matrix operator/(const Number &number, const Matrix &a);

    friend void operator+=(Matrix &a, const Matrix &b);
    friend void operator-=(Matrix &a, const Matrix &b);
    friend void operator*=(Matrix &a, const Matrix &b);
    friend void operator/=(Matrix &a, const Matrix &b);

    template <class Number>
    friend void operator*=(Matrix &a, const Number &number);
    template <class Number>
    friend void operator*=(const Number &number, Matrix &a);
    template <class Number>
    friend void operator/=(Matrix &a, const Number &number);
    template <class Number>
    friend void operator/=(const Number &number, Matrix &a);

    template <class Number>
    friend void pow(Number &&number, const Matrix &matrix, Matrix &output);

    template <class Number>
    friend void pow(const Matrix &matrix, Number &&number, Matrix &output);

    ELEMENT_TYPE &get(int i, int j) {
        assert(i < shape.rows && j < shape.columns);
        return data[i * shape.columns + j];
    }

    const Shape &getShape() { return shape; }

   private:
    bool equal(const Matrix &a, const Matrix &b);
    bool less(const Matrix &a, const Matrix &b);
    bool lessEqual(const Matrix &a, const Matrix &b);
    bool greater(const Matrix &a, const Matrix &b);
    bool greaterEqual(const Matrix &a, const Matrix &b);
    bool notEqual(const Matrix &a, const Matrix &b);

    void add(const Matrix &a, const Matrix &b, Matrix &output);
    void substract(const Matrix &a, const Matrix &b, Matrix &output);
    void multiply(const Matrix &a, const Matrix &b, Matrix &output);

    template <class Number>
    void multiply(const Number &number, const Matrix &a, Matrix &output);
    template <class Number>
    void multiply(const Matrix &a, const Number &number, Matrix &output);

    template <class Number>
    void divide(const Matrix &a, const Number &number, Matrix &output);
    template <class Number>
    void divide(const Number &number, const Matrix &a, Matrix &output);

    std::shared_ptr<ELEMENT_TYPE> data;
    Shape shape;
};

#endif
