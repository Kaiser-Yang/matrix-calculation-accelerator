#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cstring>
#include <memory>
#include <type_traits>
#include <vector>

namespace mca {
struct Shape {
    size_t rows    = 0;
    size_t columns = 0;

    Shape() = default;
    Shape(size_t rows, size_t columns) : rows(rows), columns(columns) {}
    bool operator==(const Shape &other) const {
        return rows == other.rows && columns == other.columns;
    }
    bool operator!=(const Shape &other) const { return !(*this == other); }

    size_t size() const { return rows * columns; }
};

template <class ELEMENT_TYPE = double>
class Matrix {
public:
    Matrix() = default;

    Matrix(const std::vector<std::vector<ELEMENT_TYPE>> &init) {
        shape.rows = init.size();
        if (init.size() != 0) { shape.columns = init[0].size(); }
        if (shape.size() != 0) {
            data = std::make_unique<ELEMENT_TYPE[]>(shape.size());
            for (size_t i = 0; i < shape.rows; i++) {
                assert(init[i].size() == shape.columns);
                for (size_t j = 0; j < shape.columns; j++) { get(i, j) = init[i][j]; }
            }
            //             TODO: update with multi thread
            //             *this         = init;
        }
    }

    Matrix(const Shape &shape, const ELEMENT_TYPE &defaultValue) {
        this->shape = shape;
        if (shape.size() != 0) {
            data = std::make_unique<ELEMENT_TYPE[]>(shape.size());
            std::fill(data.get(), data.get() + shape.size(), defaultValue);
            // TODO: update with multi thread
            //             fill(defaultValue);
        }
    }

    template <class T>
    Matrix(const Matrix<T> &other) {
        *this = other;
    }

    // only those which have the same ELEMENT_TYPE can use move constructor
    Matrix(Matrix &&other) noexcept
        : data(std::move(other.data)), shape(std::move(other.getShape())) {}

    // only those which have the same ELEMENT_TYPE can use move assignment
    Matrix &operator=(Matrix &&other) noexcept {
        shape = std::move(other.shape);
        data  = std::move(other.data);
        return *this;
    }

    ELEMENT_TYPE &get(size_t i, size_t j) {
        assert(i < shape.rows && j < shape.columns);
        return data[i * shape.columns + j];
    }

    ELEMENT_TYPE *dataPtr() { return data.get(); }
    const ELEMENT_TYPE *dataPtr() const { return data.get(); }

    const ELEMENT_TYPE &get(size_t i, size_t j) const {
        assert(i < shape.rows && j < shape.columns);
        return data[i * shape.columns + j];
    }

    size_t rows() const { return shape.rows; }
    size_t columns() const { return shape.columns; }

    Shape getShape() const { return shape; }

    void reshape(const Shape &shape) {
        assert(this->shape.size() == shape.size());
        this->shape = shape;
    }

    void fill(const ELEMENT_TYPE &value);

    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const Matrix<T> &other);

    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const std::vector<std::vector<T>> &init);

private:
    std::unique_ptr<ELEMENT_TYPE[]> data;
    Shape shape;

    template <class T1, class T2>
    friend bool operator==(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend bool operator<(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend bool operator>(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b);

    template <class T1, class T2>
    friend Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b);

    template <class T, class Number>
    friend Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a,
                                                           const Number &number);
    template <class Number, class T>
    friend Matrix<std::common_type_t<T, Number>> operator+(const Number &number,
                                                           const Matrix<T> &a);
    template <class T, class Number>
    friend Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a,
                                                           const Number &number);
    template <class Number, class T>
    friend Matrix<std::common_type_t<T, Number>> operator-(const Number &number,
                                                           const Matrix<T> &a);
    template <class T, class Number>
    friend Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a,
                                                           const Number &number);
    template <class Number, class T>
    friend Matrix<std::common_type_t<T, Number>> operator*(const Number &number,
                                                           const Matrix<T> &a);
    template <class T, class Number>
    friend Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a,
                                                           const Number &number);
    template <class Number, class T>
    friend Matrix<std::common_type_t<T, Number>> operator/(const Number &number,
                                                           const Matrix<T> &a);

    template <class T>
    friend Matrix<T> operator-(Matrix<T> &a);

    template <class T1, class T2>
    friend void operator+=(Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend void operator-=(Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend void operator*=(Matrix<T1> &a, const Matrix<T2> &b);
    template <class T1, class T2>
    friend void operator/=(Matrix<T1> &a, const Matrix<T2> &b);

    template <class T, class Number>
    friend void operator+=(Matrix<T> &a, const Number &number);
    template <class Number, class T>
    friend void operator+=(const Number &number, Matrix<T> &a);
    template <class T, class Number>
    friend void operator-=(Matrix<T> &a, const Number &number);
    template <class Number, class T>
    friend void operator-=(const Number &number, Matrix<T> &a);
    template <class T, class Number>
    friend void operator*=(Matrix<T> &a, const Number &number);
    template <class Number, class T>
    friend void operator*=(const Number &number, Matrix<T> &a);
    template <class T, class Number>
    friend void operator/=(Matrix<T> &a, const Number &number);
    template <class Number, class T>
    friend void operator/=(const Number &number, Matrix<T> &a);

    template <class Number, class T>
    friend void pow(Number &&number, const Matrix<T> &a);
    template <class T, class Number>
    friend void pow(const Matrix<T> &a, Number &&number);

    template <class T>
    friend Matrix<T> transpose(const Matrix<T> &a);
    template <class T>
    friend void transpose(const Matrix<T> &a, Matrix<T> &output);

    template <class T1, class T2>
    friend bool equalSingleThread(const Matrix<T1> &a,
                                  const Matrix<T2> &b,
                                  const size_t &sx,
                                  const size_t &sy,
                                  const Shape &shape,
                                  const double &eps);
    template <class T1, class T2>
    friend bool lessSingleThread(const Matrix<T1> &a,
                                 const Matrix<T2> &b,
                                 const size_t &sx,
                                 const size_t &sy,
                                 const Shape &shape,
                                 const double &eps);
    template <class T1, class T2>
    friend bool lessEqualSingleThread(const Matrix<T1> &a,
                                      const Matrix<T2> &b,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape,
                                      const double &eps);
    template <class T1, class T2>
    friend bool greaterSingleThread(const Matrix<T1> &a,
                                    const Matrix<T2> &b,
                                    const size_t &sx,
                                    const size_t &sy,
                                    const Shape &shape,
                                    const double &eps);
    template <class T1, class T2>
    friend bool greaterEqualSingleThread(const Matrix<T1> &a,
                                         const Matrix<T2> &b,
                                         const size_t &sx,
                                         const size_t &sy,
                                         const Shape &shape,
                                         const double &eps);
    template <class T1, class T2>
    friend bool notEqualSingleThread(const Matrix<T1> &a,
                                     const Matrix<T2> &b,
                                     const size_t &sx,
                                     const size_t &sy,
                                     const Shape &shape,
                                     const double &eps);

    template <class T1, class T2, class O>
    friend void addSingleThread(const Matrix<T1> &a,
                                const Matrix<T2> &b,
                                Matrix<O> &output,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape);
    template <class T1, class T2, class O>
    friend void substractSingleThread(const Matrix<T1> &a,
                                      const Matrix<T2> &b,
                                      Matrix<O> &output,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape);
    template <class T1, class T2, class O>
    friend void multiplySingleThread(const Matrix<T1> &a,
                                     const Matrix<T2> &b,
                                     Matrix<O> &output,
                                     const size_t &sx,
                                     const size_t &sy,
                                     const Shape &shape);

    template <class Number, class T, class O>
    friend void addSingleThread(const Number &number,
                                const Matrix<T> &a,
                                Matrix<O> &output,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape);
    template <class Number, class T, class O>
    friend void substractSingleThread(const Number &number,
                                      const Matrix<T> &a,
                                      Matrix<O> &output,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape);
    template <class T, class Number, class O>
    friend void substractSingleThread(const Matrix<T> &a,
                                      const Number &number,
                                      Matrix<O> &output,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape);
    template <class Number, class T, class O>
    friend void multiplySingleThread(const Number &number,
                                     const Matrix<T> &a,
                                     Matrix<O> &output,
                                     const size_t &sx,
                                     const size_t &sy,
                                     const Shape &shape);
    template <class T, class Number, class O>
    friend void divideSingleThread(const Matrix<T> &a,
                                   const Number &number,
                                   Matrix<O> &output,
                                   const size_t &sx,
                                   const size_t &sy,
                                   const Shape &shape);
    template <class Number, class T, class O>
    friend void divideSingleThread(const Number &number,
                                   const Matrix<T> &a,
                                   Matrix<O> &output,
                                   const size_t &sx,
                                   const size_t &sy,
                                   const Shape &shape);

    template <class Number, class T, class O>
    friend void powSingleThread(Number &&number,
                                const Matrix<T> &a,
                                Matrix<O> &output,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape);
    template <class T, class Number, class O>
    friend void powSingleThread(const Matrix<T> &a,
                                Number &&number,
                                Matrix<O> &output,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape);

    template <class T>
    friend void transposeSingleThread(const Matrix<T> &a,
                                      Matrix<T> &output,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape);
};

// TODO
template <class ELEMENT_TYPE>
void Matrix<ELEMENT_TYPE>::fill(const ELEMENT_TYPE &value) {}

// TODO
template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const Matrix<T> &other) {
    return *this;
}

// TODO
template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const std::vector<std::vector<T>> &init) {
    return *this;
}

}  // namespace mca

#endif
