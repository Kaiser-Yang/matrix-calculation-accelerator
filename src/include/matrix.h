#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <vector>

#include "thread_pool.h"

namespace mca {
extern ThreadPool &threadPool();

extern size_t limit();

extern size_t threadNum();

struct Shape {
    size_t rows    = 0;
    size_t columns = 0;

    Shape() = default;

    Shape(size_t rows, size_t columns);

    bool operator==(const Shape &other) const;

    bool operator!=(const Shape &other) const;

    size_t size() const;
};

template <class ELEMENT_TYPE = double>
class Matrix {
public:
    using ElementType = ELEMENT_TYPE;

    // Construct an empty matrix
    Matrix() = default;

    // Construct an identity matrix
    Matrix(const Shape &shape);

    // Construct a matrix from a initializer_list
    // You can use this like Matrix<>({{1, 2}, {3, 4}})
    // NOTE: if you use Matrix({{1, 2}, {3, 4}}) the ELEMENT_TYPE will be int rather than double
    Matrix(const std::initializer_list<std::initializer_list<ELEMENT_TYPE>> &init);

    // Construct a matrix from a vector
    Matrix(const std::vector<std::vector<ELEMENT_TYPE>> &init);

    // Construct a matrix with shape and defaultValue
    inline Matrix(const Shape &shape, const ELEMENT_TYPE &defaultValue);

    // Construct a diagonal matrix, the diag is the diagonal elements
    // Matrix<>({1, 2, 3, 4}) will construct a matrix whose shape are 4 * 4,
    // and diagonal elements are 1, 2, 3, 4 other elements will be ELEMENT_TYPE()
    // In this case, double() will be 0
    Matrix(const std::initializer_list<ELEMENT_TYPE> &diag);

    // Copy constructor
    // If the other matrix's ELEMENT_TYPE is not same with current matrix,
    // the other matrix's data will use static_cast<> to convert its type the same with current
    // matrix
    template <class T>
    inline Matrix(const Matrix<T> &other);

    // Move constructor
    // NOTE: only those which have the same ELEMENT_TYPE can use move constructor
    inline Matrix(Matrix &&other) noexcept;

    // Move assignment
    // NOTE: only those which have the same ELEMENT_TYPE can use move assignment
    inline Matrix &operator=(Matrix &&other) noexcept;

    // Copy assignment
    // If the other matrix's ELEMENT_TYPE is not same with current matrix,
    // the other matrix's data will use static_cast<> to convert its type the same with current
    // matrix
    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const Matrix<T> &other);

    // Copy assignment from a initializer_list
    // You can use this like: matrix = {{1, 2}, {3, 4}}
    // If the initializer_list's T is not same with current matrix,
    // the initializer_list's data will use static_cast<> to convert its type the same with current
    // matrix
    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const std::initializer_list<std::initializer_list<T>> &init);

    // Copy assignment from a vector
    // If the vector's T is not same with current matrix,
    // the vector's data will use static_cast<> to convert its type the same with current
    // matrix
    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const std::vector<std::vector<T>> &init);

    // get the reference to the element of i-th row, j-th column
    inline ELEMENT_TYPE &get(size_t i, size_t j);
    inline const ELEMENT_TYPE &get(size_t i, size_t j) const;

    // get the date pointer
    inline ELEMENT_TYPE *dataPtr();
    inline const ELEMENT_TYPE *dataPtr() const;

    // get the number of rows
    inline size_t rows() const;

    // get the number of columns
    inline size_t columns() const;

    // get the number of elements
    inline size_t size() const;

    // get the matrix's shape
    inline Shape getShape() const;

    // Reshape the matrix
    // NOTE: this is only valid, when the new shape has the same number of elements with the old
    //       one
    inline void reshape(const Shape &shape);

    // Make all the elements of the matrix be a new value
    void fill(const ELEMENT_TYPE &value);

    // Calculate number ^ (*this), and store the result in output
    // If the output is nullptr, (*this) will be changed
    // NOTE: (*this) must have the same shape with output
    //       If O and ELEMENT_TYPE are not same, all the elements will first be cast to
    //       std::common_type<O, ELEMENT_TYPE>, after calculation they will be cast into O
    //       by using static_cast
    // for example: a = [[1, 2, 3],
    //                   [2, 3, 4]]
    //              a.numberPow(2, output)
    //              output: [[2^1, 2^2, 2^3],
    //                       [2^2, 2^3, 2^4]]
    //              a.numberPow(2)
    //              a: [[2^1, 2^2, 2^3],
    //                  [2^2, 2^3, 2^4]]
    template <class Number, class O>
    void numberPow(Number &&number, const Matrix<O> &output = nullptr);

    // Calculate (*this) ^ number, and store the result in output
    // If the output is nullptr, (*this) will be changed
    // NOTE: (*this) must have the same shape with output
    //       If O and ELEMENT_TYPE are not same, all the elements will first be cast to
    //       std::common_type<O, ELEMENT_TYPE>, after calculation they will be cast into O
    //       by using static_cast
    // for example: a = [[1, 2, 3],
    //                   [2, 3, 4]]
    //              a.powNumber(2, output)
    //              output: [[1^2, 2^2, 3^2],
    //                       [2^2, 3^2, 4^2]]
    //              a.numberPow(2)
    //              a: [[1^2, 2^2, 3^2],
    //                  [2^2, 3^2, 4^2]]
    template <class Number, class O>
    void powNumber(Number &&number, const Matrix<O> &output = nullptr);

    // Calculate (*this) ^ exponent, and store the result in output
    // This is different with powNumber or numberPow
    // This will calculate the matrix exponentiation
    // This is only valid when (*this) is a square matrix
    // NOTE: (*this) must be a square matrix
    //       (*this) must have the same shape with output
    //       If O and ELEMENT_TYPE are not same, all the elements will first be cast to
    //       std::common_type<O, ELEMENT_TYPE>, after calculation they will be cast into O
    //       by using static_cast
    // for example: a = [[1, 2],
    //                   [2, 3]]
    //              a.pow(2, output)
    //              output = [[5, 8],
    //                        [8, 13]]
    template <class O>
    void pow(size_t exponent, Matrix<O> &output = nullptr);

    // Transpose (*this), and store the result in output
    // If the output is nullptr, (*this) will be changed
    // NOTE: output must have the same shape with the current matrix after transposition
    //       If O and ELEMENT_TYPE are not same, all the elements will first be cast to
    //       std::common_type<O, ELEMENT_TYPE>, after calculation they will be cast into O
    //       by using static_cast
    // for example: a = [[1, 2, 3],
    //                   [2, 3, 4]]
    //              a.powNumber(2, output)
    //              output: [[1, 2],
    //                       [2, 3],
    //                       [3, 4]]
    //              a.numberPow(2)
    //              a: [[1, 2],
    //                  [2, 3],
    //                  [3, 4]]
    template <class O>
    void transpose(Matrix<O> &output = nullptr);

    // Check if the matrix is symmetric with multi-thread
    bool symmetric();

    // Check if the matrix is antisymmetric with multi-thread
    bool antisymmetric();

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
    friend void subtractSingleThread(const Matrix<T1> &a,
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
    friend void subtractSingleThread(const Number &number,
                                     const Matrix<T> &a,
                                     Matrix<O> &output,
                                     const size_t &sx,
                                     const size_t &sy,
                                     const Shape &shape);
    template <class T, class Number, class O>
    friend void subtractSingleThread(const Matrix<T> &a,
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
    friend void numberPowSingleThread(Number &&number,
                                      const Matrix<T> &a,
                                      Matrix<O> &output,
                                      const size_t &sx,
                                      const size_t &sy,
                                      const Shape &shape);
    template <class T, class Number, class O>
    friend void powNumberSingleThread(const Matrix<T> &a,
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

    template <class T>
    friend bool symmetricSingleThread(const Matrix<T> &a,
                                      const size_t &sx,
                                      const size_t rows,
                                      const double &eps);
    template <class T>
    friend bool antisymmetricSingleThread(const Matrix<T> &a,
                                          const size_t &sx,
                                          const size_t rows,
                                          const double &eps);
};

inline Shape::Shape(size_t rows, size_t columns) : rows(rows), columns(columns) {}

inline bool Shape::operator==(const Shape &other) const {
    return rows == other.rows && columns == other.columns;
}

inline bool Shape::operator!=(const Shape &other) const { return !(*this == other); }

inline size_t Shape::size() const { return rows * columns; }

// TODO
template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const Shape &shape) {}

// TODO
template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(
    const std::initializer_list<std::initializer_list<ELEMENT_TYPE>> &init) {
    shape.rows = init.size();
    if (init.size() != 0) { shape.columns = init.begin()->size(); }
    if (shape.size() != 0) {
        data     = std::make_unique<ELEMENT_TYPE[]>(shape.size());
        size_t i = 0;
        for (auto &&rows : init) {
            assert(rows.size() == shape.columns);
            size_t j = 0;
            for (auto &&item : rows) {
                get(i, j) = item;
                j++;
            }
            i++;
        }
        //             TODO: update with multi thread
        //             *this         = init;
    }
}

// TODO
template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const std::vector<std::vector<ELEMENT_TYPE>> &init) {
    shape.rows = init.size();
    if (init.size() != 0) { shape.columns = init.begin()->size(); }
    if (shape.size() != 0) {
        data = std::make_unique<ELEMENT_TYPE[]>(shape.size());
        for (size_t i = 0; i < rows(); i++) {
            assert(columns() == init[i].size());
            for (size_t j = 0; j < columns(); j++) { get(i, j) = init[i][j]; }
        }
        //             TODO: update with multi thread
        //             *this         = init;
    }
}

// TODO
template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(const Shape &shape, const ELEMENT_TYPE &defaultValue) {
    this->shape = shape;
    if (shape.size() != 0) {
        data = std::make_unique<ELEMENT_TYPE[]>(shape.size());
        std::fill(data.get(), data.get() + shape.size(), defaultValue);
        // TODO: update with multi thread
        //             fill(defaultValue);
    }
}

// TODO
template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const std::initializer_list<ELEMENT_TYPE> &diag) {}

// TODO: not finished yet, once copy assignment finishs, this will finish
template <class ELEMENT_TYPE>
template <class T>
inline Matrix<ELEMENT_TYPE>::Matrix(const Matrix<T> &other) {
    *this = other;
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(Matrix &&other) noexcept {
    *this = std::move(other);
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(Matrix &&other) noexcept {
    shape = std::move(other.shape);
    data  = std::move(other.data);
    return *this;
}

// TODO
template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const Matrix<T> &other) {
    return *this;
}

// TODO
template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(
    const std::initializer_list<std::initializer_list<T>> &init) {
    return *this;
}

// TODO
template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const std::vector<std::vector<T>> &init) {
    return *this;
}

template <class ELEMENT_TYPE>
inline ELEMENT_TYPE &Matrix<ELEMENT_TYPE>::get(size_t i, size_t j) {
    assert(i < shape.rows && j < shape.columns);
    return data[i * shape.columns + j];
}
template <class ELEMENT_TYPE>
inline const ELEMENT_TYPE &Matrix<ELEMENT_TYPE>::get(size_t i, size_t j) const {
    assert(i < shape.rows && j < shape.columns);
    return data[i * shape.columns + j];
}
template <class ELEMENT_TYPE>
inline ELEMENT_TYPE *Matrix<ELEMENT_TYPE>::dataPtr() {
    return data.get();
}

template <class ELEMENT_TYPE>
inline const ELEMENT_TYPE *Matrix<ELEMENT_TYPE>::dataPtr() const {
    return data.get();
}

template <class ELEMENT_TYPE>
inline size_t Matrix<ELEMENT_TYPE>::rows() const {
    return shape.rows;
}

template <class ELEMENT_TYPE>
inline size_t Matrix<ELEMENT_TYPE>::columns() const {
    return shape.columns;
}

template <class ELEMENT_TYPE>
inline size_t Matrix<ELEMENT_TYPE>::size() const {
    return shape.size();
}

template <class ELEMENT_TYPE>
inline Shape Matrix<ELEMENT_TYPE>::getShape() const {
    return shape;
}

template <class ELEMENT_TYPE>
inline void Matrix<ELEMENT_TYPE>::reshape(const Shape &shape) {
    assert(this->shape.size() == shape.size());
    this->shape = shape;
}

template <class ELEMENT_TYPE>
void Matrix<ELEMENT_TYPE>::fill(const ELEMENT_TYPE &value) {
    // single mode
    if (threadNum() == 0 || limit() > size()) {
        std::fill(dataPtr(), dataPtr() + size(), value);
        return;
    }
    // calculate the calculation of every thread
    size_t threadCalculation = std::max<size_t>(size() / (threadNum() + 1), limit());

    // calculate how many sub-thread will join this calculation
    size_t taskNum = size() / threadCalculation;

    if (size() % threadCalculation > 0) { taskNum++; }

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(taskNum - 1);
    // assign task for every sub-thread
    for (size_t i = 0; i < taskNum - 1; i++) {
        returnValue[i] = threadPool().addTask([this, i, threadCalculation, value]() {
            std::fill(
                dataPtr() + i * threadCalculation, dataPtr() + (i + 1) * threadCalculation, value);
        });
    }
    // let main thread calculate two
    std::fill(dataPtr() + (taskNum - 1) * threadCalculation, dataPtr() + size(), value);

    // make sure all the sub threads are finished
    for (size_t i = 0; i < taskNum - 1; i++) { returnValue[i].get(); }
}

// TODO
template <class ELEMENT_TYPE>
template <class Number, class O>
void Matrix<ELEMENT_TYPE>::numberPow(Number &&number, const Matrix<O> &output) {}

// TODO
template <class ELEMENT_TYPE>
template <class Number, class O>
void Matrix<ELEMENT_TYPE>::powNumber(Number &&number, const Matrix<O> &output) {}

// TODO
template <class ELEMENT_TYPE>
template <class O>
void Matrix<ELEMENT_TYPE>::pow(size_t exponent, Matrix<O> &output) {}

// TODO
template <class ELEMENT_TYPE>
template <class O>
void Matrix<ELEMENT_TYPE>::transpose(Matrix<O> &output) {}

}  // namespace mca

#endif
