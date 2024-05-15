#ifndef SINGLE_THREAD_MATRIX_CALCULATION
#define SINGLE_THREAD_MATRIX_CALCULATION

#include <cmath>
#include <type_traits>

#include "matrix.h"

namespace mca {

// Calculate number ^ a, and store the result in output
// This will only calculate the number^a[pos: pos + len] in the matrix
// pos: one-demensional starting index of the matrix
// len: number of elements to be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              pos = 1
//              len = 4
//              output = [[origin, 2^2, 2^3],
//                        [2^2, 2^3, origin]]
template <class Number, class T, class O>
void numberPowSingleThread(Number &&number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len);

// Calculate a ^ number, and store the result in output
// This will only calculate the a^number[pos: pos + len] in the matrix
// pos: one-demensional starting index of the matrix
// len: number of elements to be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              pos = 1
//              len = 4
//              output = [[origin, 2^2, 3^2],
//                        [2^2, 3^2, origin]]
template <class T, class Number, class O>
void powNumberSingleThread(const Matrix<T> &a,
                           Number &&number,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len);

// Check if the elements of the sub-matrix of a are all less than the sub-matrix of b's
// This will only check the a[pos:pos+len] with b[pos:pos+len]
// pos: one-demensional starting index of the matrix
// len: number of elements to be checked
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool lessSingleThread(const Matrix<T1> &a,
                      const Matrix<T2> &b,
                      const size_t &pos,
                      const size_t &len,
                      const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all equal with the sub-matrix of b's
// This will only check the a.dataPtr()[pos:pos+len] with b.dataPtr()[pos:pos+len]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool equalSingleThread(const Matrix<T1> &a,
                       const Matrix<T2> &b,
                       const size_t &pos,
                       const size_t &len,
                       const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all less than or equal with the sub-matrix of
// This will only check the a[pos:pos+len] with b[pos:pos+len]
// pos: one-demensional starting index of the matrix
// len: number of elements to be checked
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool lessEqualSingleThread(const Matrix<T1> &a,
                           const Matrix<T2> &b,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all greater than the sub-matrix of b's
// This will only check the a[pos:pos+len] with b[pos:pos+len]
// pos: one-demensional starting index of the matrix
// len: number of elements to be checked
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool greaterSingleThread(const Matrix<T1> &a,
                         const Matrix<T2> &b,
                         const size_t &pos,
                         const size_t &len,
                         const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all greater than or equal with the sub-matrix of
// b's This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool greaterEqualSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &sx,
                              const size_t &sy,
                              const Shape &shape,
                              const double &eps = 1e-100);

// Check if any element of the sub-matrix of a is not equal with the sub-matrix of b's
// This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool notEqualSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape,
                          const double &eps = 1e-100);

// Calculate a + b, and store the result in output
// This will only calculate the a+b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: a = [[-1, -2, -3],
//                   [-1, -2, -3]]
//              b = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, -2+2, -3+3],
//                        [origin, -2+3, -3+4]]
template <class T1, class T2, class O>
void addSingleThread(const Matrix<T1> &a,
                     const Matrix<T2> &b,
                     Matrix<O> &output,
                     const size_t &sx,
                     const size_t &sy,
                     const Shape &shape);

// Calculate a - b, and store the result in output
// This will only calculate the a-b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: a = [[-1, -2, -3],
//                   [-1, -2, -3]]
//              b = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, -2-2, -3-3],
//                        [origin, -2-3, -3-4]]
template <class T1, class T2, class O>
void subtractSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calculate a * b, and store the result in output
// This will only calculate the a*b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
template <class T1, class T2, class O>
void multiplySingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calculate number + a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2+2, 2+3],
//                        [origin, 2+3, 2+4]]
template <class Number, class T, class O>
void addSingleThread(const Number &number,
                     const Matrix<T> &a,
                     Matrix<O> &output,
                     const size_t &sx,
                     const size_t &sy,
                     const Shape &shape);

// Calculate number - a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2-2, 2-3],
//                        [origin, 2-3, 2-4]]
template <class Number, class T, class O>
void subtractSingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calculate a - number, and store the result in output
// This will only calculate the a^number[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2-2, 3-2],
//                        [origin, 3-2, 4-2]]
template <class T, class Number, class O>
void subtractSingleThread(const Matrix<T> &a,
                          const Number &number,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calculate number * a, and store the result in output
// This will only calculate the number*a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2*2, 2*3],
//                        [origin, 2*3, 2*4]]
template <class Number, class T, class O>
void multiplySingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calculate a / number, and store the result in output
// This will only calculate the a^number[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2/2, 3/2],
//                        [origin, 3/2, 4/2]]
template <class T, class Number, class O>
void divideSingleThread(const Matrix<T> &a,
                        const Number &number,
                        Matrix<O> &output,
                        const size_t &sx,
                        const size_t &sy,
                        const Shape &shape);

// Calculate number / a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// pos: the frist position of matrix a
// len: length of elements
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              pos = 2
//              len = 4
//              output = [[origin, origin, 2/3],
//                        [2/2,    2/3,    2/4]]
template <class Number, class T, class O>
void divideSingleThread(const Number &number,
                        const Matrix<T> &a,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len);

// Transpose a matrix, and store the result in output
// This will only get the transposed output.dataPtr()[pos:pos+len]
// pos: the frist position of output
// len: length of elements
// NOTE: a must have the same shape with output after transposition
//       &a must not be equal with &output
//       the matrix which will be calculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              pos = 2
//              len = 4
//              output = [[origin, origin],
//                        [2, 3],
//                        [3, 4]]
template <class T>
void transposeSingleThread(const Matrix<T> &a,
                           Matrix<T> &output,
                           const size_t &pos,
                           const size_t &len);

// Check whether or not rows of matrix are symmetric
// pos: start position from the first element which will be used
// len: length of elements
// NOTE: a must be a square matrix
//       pos + len must less than or equal with (a.size() - a.rows())/2
// for example: a = [[1, 2, 3],
//                   [2, 3, 4],
//                   [3, 6, 5]]
//              pos = 0
//              len = 2
//              return: true
template <class T>
bool symmetricSingleThread(const Matrix<T> &a,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps = 1e-100);

// Check whether or not rows of matrix are antisymmetric
// pos: start pos from the first element which will be used
// len: length of elements
// NOTE: a must be a square matrix
//       pos + len must less than or equal with (a.size() - a.rows())/2
// for example: a = [[1,  2, 3],
//                   [2,  3, 4],
//                   [3, -4, 5]]
//              pos = 2 (pos 2's element is 4)
//              len = 1
//              return: true
template <class T>
bool antisymmetricSingleThread(const Matrix<T> &a,
                               const size_t &pos,
                               const size_t &len,
                               const double &eps = 1e-100);

// Those below are the implementations
template <class Number, class T, class O>
void numberPowSingleThread(Number &&number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output.dataPtr()[i] = static_cast<O>(
            std::pow(static_cast<CommonType>(number), static_cast<CommonType>(a.dataPtr()[i])));
    }
}

template <class T, class Number, class O>
void powNumberSingleThread(const Matrix<T> &a,
                           Number &&number,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output.dataPtr()[i] = static_cast<O>(
            std::pow(static_cast<CommonType>(a.dataPtr()[i]), static_cast<CommonType>(number)));
    }
}

template <class T1, class T2>
bool lessSingleThread(const Matrix<T1> &a,
                      const Matrix<T2> &b,
                      const size_t &pos,
                      const size_t &len,
                      const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a.dataPtr()[i]) - static_cast<CommonType>(b.dataPtr()[i]) >=
                -eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            (static_cast<CommonType>(a.dataPtr()[i]) >= static_cast<CommonType>(b.dataPtr()[i]))) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool equalSingleThread(const Matrix<T1> &a,
                       const Matrix<T2> &b,
                       const size_t &pos,
                       const size_t &len,
                       const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    size_t i = 0, j = 0;
    for (size_t t = pos; t < pos + len; t++) {
        i = t / a.columns();
        j = t % a.columns();
        if (std::is_floating_point_v<CommonType> &&
            std::fabs(static_cast<CommonType>(a.get(i, j)) - static_cast<CommonType>(b.get(i, j))) >
                eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a.get(i, j)) != static_cast<CommonType>(b.get(i, j))) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool lessEqualSingleThread(const Matrix<T1> &a,
                           const Matrix<T2> &b,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a.dataPtr()[i]) - static_cast<CommonType>(b.dataPtr()[i]) >
                eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a.dataPtr()[i]) > static_cast<CommonType>(b.dataPtr()[i])) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool greaterSingleThread(const Matrix<T1> &a,
                         const Matrix<T2> &b,
                         const size_t &pos,
                         const size_t &len,
                         const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            (static_cast<CommonType>(a.dataPtr()[i]) - static_cast<CommonType>(b.dataPtr()[i]) <
                 eps ||
             fabs(static_cast<CommonType>(a.dataPtr()[i]) -
                  static_cast<CommonType>(b.dataPtr()[i])) <= eps)) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a.dataPtr()[i]) <= static_cast<CommonType>(b.dataPtr()[i])) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool greaterEqualSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &sx,
                              const size_t &sy,
                              const Shape &shape,
                              const double &eps) {
    assert(a.shape() == b.shape());
    assert(sx + shape.rows <= a.rows());
    assert(sy + shape.columns <= a.columns());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) - static_cast<CommonType>(b.get(i, j)) <
                    -eps) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) < static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class T1, class T2>
bool notEqualSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape,
                          const double &eps) {
    assert(a.shape() == b.shape());
    assert(sx + shape.rows <= a.rows());
    assert(sy + shape.columns <= a.columns());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                std::fabs(static_cast<CommonType>(a.get(i, j)) -
                          static_cast<CommonType>(b.get(i, j))) <= eps) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) == static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class Number, class T, class O>
void multiplySingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(number) *
                                              static_cast<CommonType>(a.get(i, j)));
        }
    }
}

template <class T1, class T2, class O>
void addSingleThread(const Matrix<T1> &a,
                     const Matrix<T2> &b,
                     Matrix<O> &output,
                     const size_t &sx,
                     const size_t &sy,
                     const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == b.shape());
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(a.get(i, j)) +
                                              static_cast<CommonType>(b.get(i, j)));
        }
    }
}

template <class T1, class T2, class O>
void subtractSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == b.shape());
    assert(sx + shape.rows <= a.rows());
    assert(sy + shape.columns <= a.columns());
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(a.get(i, j)) -
                                              static_cast<CommonType>(b.get(i, j)));
        }
    }
}

template <class T1, class T2, class O>
void multiplySingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.columns() == b.rows());
    assert(a.rows() == output.rows());
    assert(b.columns() == output.columns());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = 0;
            for (size_t k = 0; k < a.columns(); k++) {
                // clang-format off
                output.get(i, j) = static_cast<O>(static_cast<CommonType>(output.get(i, j)) +
                                                  static_cast<CommonType>(a.get(i, k)) *
                                                  static_cast<CommonType>(b.get(k, j)));
                // clang-format on
            }
        }
    }
}

template <class Number, class T, class O>
void addSingleThread(const Number &number,
                     const Matrix<T> &a,
                     Matrix<O> &output,
                     const size_t &sx,
                     const size_t &sy,
                     const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(number) +
                                              static_cast<CommonType>(a.get(i, j)));
        }
    }
}

template <class Number, class T, class O>
void subtractSingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(number) -
                                              static_cast<CommonType>(a.get(i, j)));
        }
    }
}
template <class T, class Number, class O>
void subtractSingleThread(const Matrix<T> &a,
                          const Number &number,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(a.get(i, j)) -
                                              static_cast<CommonType>(number));
        }
    }
}

template <class T, class Number, class O>
void divideSingleThread(const Matrix<T> &a,
                        const Number &number,
                        Matrix<O> &output,
                        const size_t &sx,
                        const size_t &sy,
                        const Shape &shape) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(sx + shape.rows <= output.rows());
    assert(sy + shape.columns <= output.columns());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(a.get(i, j)) /
                                              static_cast<CommonType>(number));
        }
    }
}

template <class Number, class T, class O>
void divideSingleThread(const Number &number,
                        const Matrix<T> &a,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    size_t i = 0, j = 0;
    for (size_t t = pos; t < pos + len; t++) {
        i = t / a.columns();
        j = t % a.columns();
        output.get(i, j) =
            static_cast<O>(static_cast<CommonType>(number) / static_cast<CommonType>(a.get(i, j)));
    }
}

template <class T>
void transposeSingleThread(const Matrix<T> &a,
                           Matrix<T> &output,
                           const size_t &pos,
                           const size_t &len) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.rows() == output.columns());
    assert(a.columns() == output.rows());
    assert(pos + len <= output.size());
    size_t i = 0, j = 0;
    for (size_t t = pos; t < pos + len; t++) {
        i                = t / output.columns();
        j                = t % output.columns();
        output.get(i, j) = a.get(j, i);
    }
}

template <class T>
bool symmetricSingleThread(const Matrix<T> &a,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps) {
    assert(a.rows() == a.columns());
    assert(pos + len <= (a.size() - a.rows()) / 2);
    size_t i = 0, j = 0, k = 0;
    for (size_t t = pos; t < pos + len; t++) {
        k = std::ceil((-1 + std::sqrt(1 + 4 * a.rows() * a.rows() - 4 * a.rows() - 8 * t) / 2.0));
        i = a.rows() - 1 - k;
        j = a.rows() - (a.rows() * (a.rows() - 1) / 2 - k * (k - 1) / 2);
        if (std::is_floating_point_v<T> && fabs(a.get(i, j) - a.get(j, i)) > eps) {
            return false;
        } else if (!std::is_floating_point_v<T> && a.get(i, j) != a.get(j, i)) {
            return false;
        }
    }
    return true;
}

template <class T>
bool antisymmetricSingleThread(const Matrix<T> &a,
                               const size_t &pos,
                               const size_t &len,
                               const double &eps) {
    assert(a.rows() == a.columns());
    assert(pos + len <= (a.size() - a.rows()) / 2);
    size_t i = 0, j = 0, k = 0;
    for (size_t t = pos; t < pos + len; t++) {
        k = std::ceil((-1 + std::sqrt(1 + 4 * a.rows() * a.rows() - 4 * a.rows() - 8 * t) / 2.0));
        i = a.rows() - 1 - k;
        j = a.rows() - (a.rows() * (a.rows() - 1) / 2 - k * (k - 1) / 2);
        if (std::is_floating_point_v<T> && fabs(a.get(i, j) + a.get(j, i)) > eps) {
            return false;
        } else if (!std::is_floating_point_v<T> && a.get(i, j) != -a.get(j, i)) {
            return false;
        }
    }
    return true;
}
}  // namespace mca
#endif
