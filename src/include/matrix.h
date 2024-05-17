#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "matrix_declaration.h"
#include "mca.h"

namespace mca {
struct Shape {
    size_t rows    = 0;
    size_t columns = 0;

    Shape() = default;

    Shape(size_t rows, size_t columns);

    bool operator==(const Shape &other) const;

    bool operator!=(const Shape &other) const;

    size_t size() const;
};

template <class ELEMENT_TYPE>
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
    inline Matrix(const std::initializer_list<std::initializer_list<ELEMENT_TYPE>> &init);

    // Construct a matrix from a vector
    inline Matrix(const std::vector<std::vector<ELEMENT_TYPE>> &init);

    // Construct a matrix from a pointer
    // when len is less than shape.size(), the rest part will be filled with ELEMENT_TYPE()
    inline Matrix(const Shape &shape, const ELEMENT_TYPE *data, const size_t &len);

    // Construct a matrix with shape and defaultValue
    inline Matrix(const Shape &shape, const ELEMENT_TYPE &defaultValue);

    // Construct a diagonal matrix, the diag is the diagonal elements
    // Matrix<>({1, 2, 3, 4}) will construct a matrix whose shape is 4 * 4,
    // and diagonal elements are 1, 2, 3, 4 other elements will be ELEMENT_TYPE()
    // In this case, double() will be 0
    Matrix(const std::initializer_list<ELEMENT_TYPE> &diag);
    Matrix(const std::vector<ELEMENT_TYPE> &diag);

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
    Matrix<ELEMENT_TYPE> &operator=(const Matrix &other);

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

    // Copy assignment from a pointer
    // If the T is not same with current matrix,
    // the data will use static_cast<> to convert its type the same with current
    // size() should be less than or equal with the data's size
    template <class T>
    Matrix<ELEMENT_TYPE> &operator=(const T *data);

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
    inline Shape shape() const;

    // Reshape the matrix
    // NOTE: this is only valid, when the new shape has the same number of elements with the old
    //       one
    inline void reshape(const Shape &shape);

    // Make all the elements of the matrix be a new value, when pos = 0
    // Otherwise, the elements before pos will not changed
    // pos should be less than or equal with size()
    void fill(const ELEMENT_TYPE &value, const size_t &pos = 0);

    // Calculate number ^ (*this), and store the result in output
    // The function whose parameters do not include output will change (*this)
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
    void numberPow(const Number &number, Matrix<O> &output);
    template <class Number>
    void numberPow(const Number &number);

    // Calculate (*this) ^ number, and store the result in output
    // The function whose parameters do not include output will change (*this)
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
    void powNumber(const Number &number, Matrix<O> &output);
    template <class Number>
    inline void powNumber(const Number &number);

    // Calculate (*this) ^ exponent, and store the result in output
    // This is different with powNumber or numberPow
    // This will calculate the matrix exponentiation
    // This is only valid when (*this) is a square matrix
    // The function whose parameters do not include output will change (*this)
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
    void pow(size_t exponent, Matrix<O> &output);
    void pow(size_t exponent);

    // Transpose (*this), and store the result in output
    // The function whose parameters do not include output will change (*this)
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
    void transpose(Matrix<O> &output);
    void transpose();

    // Check if the matrix is symmetric with multi-thread
    bool symmetric();

    // Check if the matrix is antisymmetric with multi-thread
    bool antisymmetric();

private:
    std::unique_ptr<ELEMENT_TYPE[]> data;
    Shape _shape;
    size_t capacity{0};

    //     template <class T1, class T2>
    //     friend bool operator==(const Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend bool operator<(const Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend bool operator>(const Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b);
    //
    //     template <class T1, class T2>
    //     friend Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2>
    //     &b); template <class T1, class T2> friend Matrix<std::common_type_t<T1, T2>>
    //     operator-(const Matrix<T1> &a, const Matrix<T2> &b); template <class T1, class T2> friend
    //     Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b);
    //
    //     template <class T, class Number>
    //     friend Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a,
    //                                                            const Number &number);
    //     template <class Number, class T>
    //     friend Matrix<std::common_type_t<T, Number>> operator+(const Number &number,
    //                                                            const Matrix<T> &a);
    //     template <class T, class Number>
    //     friend Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a,
    //                                                            const Number &number);
    //     template <class Number, class T>
    //     friend Matrix<std::common_type_t<T, Number>> operator-(const Number &number,
    //                                                            const Matrix<T> &a);
    //     template <class T, class Number>
    //     friend Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a,
    //                                                            const Number &number);
    //     template <class Number, class T>
    //     friend Matrix<std::common_type_t<T, Number>> operator*(const Number &number,
    //                                                            const Matrix<T> &a);
    //     template <class T, class Number>
    //     friend Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a,
    //                                                            const Number &number);
    //     template <class Number, class T>
    //     friend Matrix<std::common_type_t<T, Number>> operator/(const Number &number,
    //                                                            const Matrix<T> &a);
    //
    //     template <class T1, class T2>
    //     friend void operator+=(Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend void operator-=(Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend void operator*=(Matrix<T1> &a, const Matrix<T2> &b);
    //     template <class T1, class T2>
    //     friend void operator/=(Matrix<T1> &a, const Matrix<T2> &b);
    //
    //     template <class T, class Number>
    //     friend void operator+=(Matrix<T> &a, const Number &number);
    //     template <class Number, class T>
    //     friend void operator+=(const Number &number, Matrix<T> &a);
    //     template <class T, class Number>
    //     friend void operator-=(Matrix<T> &a, const Number &number);
    //     template <class Number, class T>
    //     friend void operator-=(const Number &number, Matrix<T> &a);
    //     template <class T, class Number>
    //     friend void operator*=(Matrix<T> &a, const Number &number);
    //     template <class Number, class T>
    //     friend void operator*=(const Number &number, Matrix<T> &a);
    //     template <class T, class Number>
    //     friend void operator/=(Matrix<T> &a, const Number &number);
    //     template <class Number, class T>
    //     friend void operator/=(const Number &number, Matrix<T> &a);
};

inline Shape::Shape(size_t rows, size_t columns) : rows(rows), columns(columns) {}

inline bool Shape::operator==(const Shape &other) const {
    return rows == other.rows && columns == other.columns;
}

inline bool Shape::operator!=(const Shape &other) const { return !(*this == other); }

inline size_t Shape::size() const { return rows * columns; }

template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const Shape &shape) {
    if (shape.size() == 0) { return; }
    _shape   = shape;
    capacity = size();
    data     = std::make_unique<ELEMENT_TYPE[]>(size());
    fill(ELEMENT_TYPE());
    size_t totalCalculation = std::min(rows(), columns());
    if (threadNum() == 0 || limit() > totalCalculation) {
        for (size_t i = 0; i < totalCalculation; i++) { get(i, i) = ELEMENT_TYPE(1); }
        return;
    }
    auto res = threadCalculationTaskNum(totalCalculation);
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first]() {
                for (size_t i = start; i < end; i++) { get(i, i) = ELEMENT_TYPE(1); }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < totalCalculation; i++) {
        get(i, i) = ELEMENT_TYPE(1);
    }
    for (auto &item : returnValue) { item.get(); }
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(
    const std::initializer_list<std::initializer_list<ELEMENT_TYPE>> &init) {
    *this = init;
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(const std::vector<std::vector<ELEMENT_TYPE>> &init) {
    *this = init;
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(const Shape &shape,
                                    const ELEMENT_TYPE *data,
                                    const size_t &len) {
    if (shape.size() == 0) { return; }
    capacity   = shape.size();
    this->data = std::make_unique<ELEMENT_TYPE[]>(shape.size());
    _shape     = {std::min(len, shape.size()), 1};
    *this      = data;
    _shape     = shape;
    if (size() <= len) { return; }
    fill(0, len);
}

template <class ELEMENT_TYPE>
inline Matrix<ELEMENT_TYPE>::Matrix(const Shape &shape, const ELEMENT_TYPE &defaultValue) {
    _shape = shape;
    if (shape.size() != 0) {
        capacity = size();
        data     = std::make_unique<ELEMENT_TYPE[]>(size());
        fill(defaultValue);
    }
}

template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const std::initializer_list<ELEMENT_TYPE> &diag) {
    if (diag.size() == 0) { return; }
    _shape = {diag.size(), diag.size()};
    data   = std::make_unique<ELEMENT_TYPE[]>(size());
    fill(ELEMENT_TYPE());
    if (threadNum() == 0 || limit() > rows()) {
        for (size_t i = 0; i < rows(); i++) { get(i, i) = std::data(diag)[i]; }
        return;
    }
    auto res = threadCalculationTaskNum(rows());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, &diag, start = i * res.first, end = (i + 1) * res.first]() {
                for (size_t i = start; i < end; i++) { get(i, i) = std::data(diag)[i]; }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < rows(); i++) {
        get(i, i) = std::data(diag)[i];
    }
    for (auto &item : returnValue) { item.get(); }
}

template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE>::Matrix(const std::vector<ELEMENT_TYPE> &diag) {
    if (diag.size() == 0) { return; }
    _shape = {diag.size(), diag.size()};
    data   = std::make_unique<ELEMENT_TYPE[]>(size());
    fill(ELEMENT_TYPE());
    if (threadNum() == 0 || limit() > rows()) {
        for (size_t i = 0; i < rows(); i++) { get(i, i) = diag[i]; }
        return;
    }
    auto res = threadCalculationTaskNum(rows());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, &diag, start = i * res.first, end = (i + 1) * res.first]() {
                for (size_t i = start; i < end; i++) { get(i, i) = diag[i]; }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < rows(); i++) { get(i, i) = diag[i]; }
    for (auto &item : returnValue) { item.get(); }
}

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
    _shape = std::move(other._shape);
    data   = std::move(other.data);
    return *this;
}

template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const Matrix<T> &other) {
    if (capacity < other.size()) {
        capacity = _shape.size();
        data     = std::make_unique<ELEMENT_TYPE[]>(other.size());
    }
    _shape = other.shape();
    if (threadNum() == 0 || limit() > size()) {
        for (size_t i = 0; i < size(); i++) {
            dataPtr()[i] = static_cast<ELEMENT_TYPE>(other.dataPtr()[i]);
        }
        return *this;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first, end = (i + 1) * res.first, &other]() {
                for (size_t i = start; i < end; i++) {
                    dataPtr()[i] = static_cast<ELEMENT_TYPE>(other.dataPtr()[i]);
                }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < res.second * res.first; i++) {
        dataPtr()[i] = static_cast<ELEMENT_TYPE>(other.dataPtr()[i]);
    }
    for (auto &item : returnValue) { item.get(); }
    return *this;
}

template <class ELEMENT_TYPE>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const Matrix &other) {
    return operator=<ELEMENT_TYPE>(other);
}

template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(
    const std::initializer_list<std::initializer_list<T>> &init) {
    _shape.rows = init.size();
    if (init.size() == 0) {
        _shape.columns = 0;
        data           = nullptr;
        return *this;
    }
    _shape.columns = init.begin()->size();
    if (size() == 0) {
        data = nullptr;
        return *this;
    }
    if (capacity < size()) {
        capacity = _shape.size();
        data     = std::make_unique<ELEMENT_TYPE[]>(size());
    }
    if (threadNum() == 0 || limit() > size()) {
        for (size_t i = 0; i < rows(); i++)
            for (size_t j = 0; j < columns(); j++) { get(i, j) = std::data(std::data(init)[i])[j]; }
        return *this;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue;
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first, end = (i + 1) * res.second, &init]() {
                for (size_t i = start; i < end; i++) {
                    dataPtr()[i] = static_cast<ELEMENT_TYPE>(
                        std::data(std::data(init)[i / columns()])[i % columns()]);
                }
            });
    }

    for (size_t i = (res.second - 1) * res.first; i < res.second * res.first; i++) {
        dataPtr()[i] =
            static_cast<ELEMENT_TYPE>(std::data(std::data(init)[i / columns()])[i % columns()]);
    }
    for (auto &item : returnValue) { item.get(); }
    return *this;
}

template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const std::vector<std::vector<T>> &init) {
    _shape.rows = init.size();
    if (init.size() == 0) {
        _shape.columns = 0;
        data           = nullptr;
        return *this;
    }
    _shape.columns = init.begin()->size();
    if (size() == 0) {
        data = nullptr;
        return *this;
    }
    if (capacity < size()) {
        capacity = size();
        data     = std::make_unique<ELEMENT_TYPE[]>(size());
    }
    if (threadNum() == 0 || limit() > size()) {
        for (size_t i = 0; i < rows(); i++)
            for (size_t j = 0; j < columns(); j++) { get(i, j) = init[i][j]; }
        return *this;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first, &init]() {
                for (size_t i = start; i < end; i++) {
                    dataPtr()[i] = static_cast<ELEMENT_TYPE>(init[i / columns()][i % columns()]);
                }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < res.second * res.first; i++) {
        dataPtr()[i] = static_cast<ELEMENT_TYPE>(init[i / columns()][i % columns()]);
    }
    for (auto &item : returnValue) { item.get(); }
    return *this;
}

template <class ELEMENT_TYPE>
template <class T>
Matrix<ELEMENT_TYPE> &Matrix<ELEMENT_TYPE>::operator=(const T *data) {
    if (threadNum() == 0 || limit() > size()) {
        for (size_t i = 0; i < size(); i++) { dataPtr()[i] = static_cast<ELEMENT_TYPE>(data[i]); }
        return *this;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first, data]() {
                for (size_t i = start; i < end; i++) {
                    dataPtr()[i] = static_cast<ELEMENT_TYPE>(data[i]);
                }
            });
    }
    for (size_t i = (res.second - 1) * res.first; i < res.second * res.first; i++) {
        dataPtr()[i] = static_cast<ELEMENT_TYPE>(data[i]);
    }
    for (auto &item : returnValue) { item.get(); }
    return *this;
}

template <class ELEMENT_TYPE>
inline ELEMENT_TYPE &Matrix<ELEMENT_TYPE>::get(size_t i, size_t j) {
    assert(i < rows() && j < columns());
    return data[i * columns() + j];
}
template <class ELEMENT_TYPE>
inline const ELEMENT_TYPE &Matrix<ELEMENT_TYPE>::get(size_t i, size_t j) const {
    assert(i < rows() && j < columns());
    return data[i * columns() + j];
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
    return _shape.rows;
}

template <class ELEMENT_TYPE>
inline size_t Matrix<ELEMENT_TYPE>::columns() const {
    return _shape.columns;
}

template <class ELEMENT_TYPE>
inline size_t Matrix<ELEMENT_TYPE>::size() const {
    return _shape.size();
}

template <class ELEMENT_TYPE>
inline Shape Matrix<ELEMENT_TYPE>::shape() const {
    return _shape;
}

template <class ELEMENT_TYPE>
inline void Matrix<ELEMENT_TYPE>::reshape(const Shape &shape) {
    assert(_shape.size() == shape.size());
    _shape = shape;
}

template <class ELEMENT_TYPE>
void Matrix<ELEMENT_TYPE>::fill(const ELEMENT_TYPE &value, const size_t &pos) {
    if (size() <= pos) { return; }
    // single mode
    if (threadNum() == 0 || limit() > size() - pos) {
        std::fill(dataPtr() + pos, dataPtr() + size(), value);
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(size());

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);
    // assign task for every sub-thread
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first + pos, end = (i + 1) * res.first + pos, &value]() {
                std::fill(dataPtr() + start, dataPtr() + end, value);
            });
    }
    // let main thread calculate too
    std::fill(dataPtr() + (res.second - 1) * res.first, dataPtr() + size(), value);

    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

// TODO
template <class ELEMENT_TYPE>
template <class Number, class O>
void Matrix<ELEMENT_TYPE>::numberPow(const Number &number, Matrix<O> &output) {}
template <class ELEMENT_TYPE>
template <class Number>
void Matrix<ELEMENT_TYPE>::numberPow(const Number &number) {}

template <class ELEMENT_TYPE>
template <class Number, class O>
void Matrix<ELEMENT_TYPE>::powNumber(const Number &number, Matrix<O> &output) {
    // single mode
    if (threadNum() == 0 || limit() > size()) {
        powNumberSingleThread(*this, number, output, 0, size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(size());

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);
    // assign task for every sub-thread
    for (size_t i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first, len = res.first, &output, &number]() {
                powNumberSingleThread(*this, number, output, start, len);
            });
    }
    // let main thread calculate took
    powNumberSingleThread(*this,
                          number,
                          output,
                          (res.second - 1) * res.first,
                          (size() - (res.second - 1) * res.first));

    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class ELEMENT_TYPE>
template <class Number>
inline void Matrix<ELEMENT_TYPE>::powNumber(const Number &number) {
    powNumber(number, *this);
}

// TODO
template <class ELEMENT_TYPE>
template <class O>
void Matrix<ELEMENT_TYPE>::pow(size_t exponent, Matrix<O> &output) {}
template <class ELEMENT_TYPE>
void Matrix<ELEMENT_TYPE>::pow(size_t exponent) {}

// TODO
template <class ELEMENT_TYPE>
template <class O>
void Matrix<ELEMENT_TYPE>::transpose(Matrix<O> &output) {}
template <class ELEMENT_TYPE>
void Matrix<ELEMENT_TYPE>::transpose() {}

}  // namespace mca

#endif
