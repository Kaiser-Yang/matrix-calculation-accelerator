#ifndef SINGLE_THREAD_MATRIX_CALCULATION
#define SINGLE_THREAD_MATRIX_CALCULATION

#include <cmath>
#include <type_traits>

#include "matrix.h"

namespace mca {

// Calcualte number ^ a, and store the result in output
// This will only calculate the number^a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2^2, 2^3],
//                        [origin, 2^3, 2^4]]
template <class Number, class T, class O>
void numberPowSingleThread(Number &&number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape);

// Calcualte a ^ number, and store the result in output
// This will only calculate the a^number[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2^2, 3^2],
//                        [origin, 3^2, 4^2]]
template <class T, class Number, class O>
void powNumberSingleThread(const Matrix<T> &a,
                           Number &&number,
                           Matrix<O> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape);

// Check if the elements of the sub-matrix of a are all less than the sub-matrix of b's
// This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
bool lessSingleThread(const Matrix<T1> &a,
                      const Matrix<T2> &b,
                      const size_t &sx,
                      const size_t &sy,
                      const Shape &shape,
                      const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all equal with the sub-matrix of b's
// This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
inline bool equalSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &sx,
                              const size_t &sy,
                              const Shape &shape,
                              const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all less than or equal with the sub-matrix of
// b's This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
inline bool lessEqualSingleThread(const Matrix<T1> &a,
                                  const Matrix<T2> &b,
                                  const size_t &sx,
                                  const size_t &sy,
                                  const Shape &shape,
                                  const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all greater than the sub-matrix of b's
// This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
inline bool greaterSingleThread(const Matrix<T1> &a,
                                const Matrix<T2> &b,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape,
                                const double &eps = 1e-100);

// Check if the elements of the sub-matrix of a are all greater than or equal with the sub-matrix of
// b's This will only check the a[sx:sx+shape.rows][sy:sy+shape+shape.columns] with
// b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// NOTE: eps will be used when T1 or T2 is floating number
template <class T1, class T2>
inline bool greaterEqualSingleThread(const Matrix<T1> &a,
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

// Calcualte a + b, and store the result in output
// This will only calculate the a+b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte a - b, and store the result in output
// This will only calculate the a-b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte a * b, and store the result in output
// This will only calculate the a*b[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output and b
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
template <class T1, class T2, class O>
void multiplySingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &sx,
                          const size_t &sy,
                          const Shape &shape);

// Calcualte number + a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte number - a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte a - number, and store the result in output
// This will only calculate the a^number[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte number * a, and store the result in output
// This will only calculate the number*a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte a / number, and store the result in output
// This will only calculate the a^number[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
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

// Calcualte number / a, and store the result in output
// This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 0, sy = 1
//              shape = {2, 2}
//              output = [[origin, 2/2, 2/3],
//                        [origin, 2/3, 2/4]]
template <class Number, class T, class O>
void divideSingleThread(const Number &number,
                        const Matrix<T> &a,
                        Matrix<O> &output,
                        const size_t &sx,
                        const size_t &sy,
                        const Shape &shape);

// Transpose a matrix, and store the result in output
// This will only get the tansposed a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
// sx: start row
// sy: start column
// shape: the shape of matrix will be calculated
// NOTE: a must have the same shape with output after tranposition
//       &a must not be equal with &output
//       the matrix which will be caculated must in range
// for example: number = 2,
//              a = [[1, 2, 3],
//                   [2, 3, 4]]
//              sx = 1, sy = 0
//              shape = {2, 2}
//              output = [[origin, origin],
//                        [2, 3],
//                        [3, 4]]
template <class T>
void transposeSingleThread(const Matrix<T> &a,
                           Matrix<T> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape);

// Those below are the implementations
template <class Number, class T, class O>
void numberPowSingleThread(Number &&number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape) {
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(
                std::pow(static_cast<CommonType>(number), static_cast<CommonType>(a.get(i, j))));
        }
    }
}

template <class T, class Number, class O>
void powNumberSingleThread(const Matrix<T> &a,
                           Number &&number,
                           Matrix<O> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape) {
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(
                std::pow(static_cast<CommonType>(a.get(i, j)), static_cast<CommonType>(number)));
        }
    }
}

template <class T1, class T2>
bool lessSingleThread(const Matrix<T1> &a,
                      const Matrix<T2> &b,
                      const size_t &sx,
                      const size_t &sy,
                      const Shape &shape,
                      const double &eps) {
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) - static_cast<CommonType>(b.get(i, j)) >=
                    -eps) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) >= static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class T1, class T2>
inline bool equalSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &sx,
                              const size_t &sy,
                              const Shape &shape,
                              const double &eps) {
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                std::fabs(static_cast<CommonType>(a.get(i, j)) -
                          static_cast<CommonType>(b.get(i, j))) > eps) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) != static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class T1, class T2>
inline bool lessEqualSingleThread(const Matrix<T1> &a,
                                  const Matrix<T2> &b,
                                  const size_t &sx,
                                  const size_t &sy,
                                  const Shape &shape,
                                  const double &eps) {
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) - static_cast<CommonType>(b.get(i, j)) > eps) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) > static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class T1, class T2>
inline bool greaterSingleThread(const Matrix<T1> &a,
                                const Matrix<T2> &b,
                                const size_t &sx,
                                const size_t &sy,
                                const Shape &shape,
                                const double &eps) {
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            if (std::is_floating_point_v<CommonType> &&
                (static_cast<CommonType>(a.get(i, j)) - static_cast<CommonType>(b.get(i, j)) <
                     eps ||
                 fabs(static_cast<CommonType>(a.get(i, j)) -
                      static_cast<CommonType>(b.get(i, j))) <= eps)) {
                return false;
            }
            if (!std::is_floating_point_v<CommonType> &&
                static_cast<CommonType>(a.get(i, j)) <= static_cast<CommonType>(b.get(i, j))) {
                return false;
            }
        }
    }
    return true;
}

template <class T1, class T2>
inline bool greaterEqualSingleThread(const Matrix<T1> &a,
                                     const Matrix<T2> &b,
                                     const size_t &sx,
                                     const size_t &sy,
                                     const Shape &shape,
                                     const double &eps) {
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
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
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == b.shape);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == b.shape);
    assert(sx + shape.rows <= a.shape.rows);
    assert(sy + shape.columns <= a.shape.columns);
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
    assert(&a != &output);
    assert(a.shape.columns == b.shape.rows);
    assert(a.shape.rows == output.shape.rows);
    assert(b.shape.columns == output.shape.columns);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = 0;
            for (size_t k = 0; k < a.shape.columns; k++) {
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
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
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
                        const size_t &sx,
                        const size_t &sy,
                        const Shape &shape) {
    assert(&a != &output);
    assert(a.shape == output.shape);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) {
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(number) /
                                              static_cast<CommonType>(a.get(i, j)));
        }
    }
}

template <class T>
void transposeSingleThread(const Matrix<T> &a,
                           Matrix<T> &output,
                           const size_t &sx,
                           const size_t &sy,
                           const Shape &shape) {
    assert(a.shape.rows == output.shape.columns);
    assert(a.shape.columns == output.shape.rows);
    assert(sx + shape.rows <= output.shape.rows);
    assert(sy + shape.columns <= output.shape.columns);
    for (size_t i = sx; i < sx + shape.rows; i++) {
        for (size_t j = sy; j < sy + shape.columns; j++) { output.get(i, j) = a.get(j, i); }
    }
}
}  // namespace mca
#endif
