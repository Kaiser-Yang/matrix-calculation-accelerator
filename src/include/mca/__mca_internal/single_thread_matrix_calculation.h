#ifndef MCA_SINGLE_THREAD_MATRIX_CALCULATION
#define MCA_SINGLE_THREAD_MATRIX_CALCULATION

#include <cassert>
#include <cmath>
#include <type_traits>

#include "matrix_declaration.h"
#include "utility.h"

namespace mca {
/* Calculate number ^ a, and store the result in output
 * This will only calculate the number^a[pos:pos+len] in the matrix
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 1
 *              len = 4
 *              output = [[origin, 2^2, 2^3],
 *                        [2^2,    2^3, origin]] */
template <class Number, class T, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void numberPowSingleThread(const Number &number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len);

/* Calculate a ^ number, and store the result in output
 * This will only calculate the a^number[pos: pos + len] in the matrix
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 1
 *              len = 4
 *              output = [[origin, 2^2, 3^2],
 *                        [2^2,    3^2, origin]] */
template <class T, class Number, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void powNumberSingleThread(const Matrix<T> &a,
                           const Number &number,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len);

/* Check if the elements of the sub-matrix of a are all less than the sub-matrix of b's
 * This will only check the a[pos:pos+len] with b[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be checked
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool lessSingleThread(const Matrix<T1> &a,
                      const Matrix<T2> &b,
                      const size_t &pos,
                      const size_t &len,
                      const double &eps = 1e-100);

/* Check if the elements of the sub-matrix of a are all equal to the sub-matrix of b's
 * This will only check the a[pos:pos+len] with b[pos:pos+len]
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool equalSingleThread(const Matrix<T1> &a,
                       const Matrix<T2> &b,
                       const size_t &pos,
                       const size_t &len,
                       const double &eps = 1e-100);

/* Check if the elements of the sub-matrix of a are all less than or equal to the sub-matrix of
 * This will only check the a[pos:pos+len] with b[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be checked
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool lessEqualSingleThread(const Matrix<T1> &a,
                           const Matrix<T2> &b,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps = 1e-100);

/* Check if the elements of the sub-matrix of a are all greater than the sub-matrix of b's
 * This will only check the a[pos:pos+len] with b[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be checked
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool greaterSingleThread(const Matrix<T1> &a,
                         const Matrix<T2> &b,
                         const size_t &pos,
                         const size_t &len,
                         const double &eps = 1e-100);

/* Check if the elements of the sub-matrix of a are all greater than or equal to the sub-matrix of
 * b's This will only check the a[pos:pos+len] with
 * b[pos:pos+len]
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool greaterEqualSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &pos,
                              const size_t &len,
                              const double &eps = 1e-100);

/* Check if any element of the sub-matrix of a is not equal to the sub-matrix of b's
 * This will only check the a[pos:pos+len] with
 * b[pos:pos+len]
 * NOTE: eps will be used when T1 or T2 is floating number */
template <class T1, class T2>
bool notEqualSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          const size_t &pos,
                          const size_t &len,
                          const double &eps = 1e-100);

/* Calculate a + b, and store the result in output
 * This will only calculate the a+b[pos:pos+len]
 * pos: start position
 * len: length of calculation
 * NOTE: a must have the same shape with output and b
 *       the matrix which will be calculated must in range
 * for example: a = [[-1, -2, -3],
 *                   [-1, -2, -3]]
 *              b = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 1
 *              len = 5
 *              output = [[origin, -2+2, -3+3],
 *                        [-1+2,   -2+3, -3+4]] */
template <class T1, class T2, class O>
void addSingleThread(const Matrix<T1> &a,
                     const Matrix<T2> &b,
                     Matrix<O> &output,
                     const size_t &pos,
                     const size_t &len);

/* Calculate a - b, and store the result in output
 * This will only calculate the a-b[pos:pos+len]
 * pos: start position
 * len: length of calculation
 * NOTE: a must have the same shape with output and b
 *       the matrix which will be calculated must in range
 * for example: a = [[-1, -2, -3],
 *                   [-1, -2, -3]]
 *              b = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 1
 *              len = 5
 *              output = [[origin, -2-2, -3-3],
 *                        [-1-2,   -2-3, -3-4]] */
template <class T1, class T2, class O>
void subtractSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len);

/* Calculate a * b, and store the result in output
 * This will only calculate the a*b[pos:pos+len]
 * pos: start position
 * len: length of calculation
 * NOTE: a must have the same shape with output and b
 *       &a must not be equal to &output
 *       the matrix which will be calculated must in range */
template <class T1, class T2, class O>
void multiplySingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len);

/* Calculate number + a, and store the result in output
 * This will only calculate the number+a[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 0, len = 4
 *              output = [[2+1, 2+2,    2+3],
 *                        [2+2, origin, origin]] */
template <class Number, class T, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void addSingleThread(const Number &number,
                     const Matrix<T> &a,
                     Matrix<O> &output,
                     const size_t &pos,
                     const size_t &len);

/* Calculate number - a, and store the result in output
 * This will only calculate the number-a[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 0, len = 4
 *              output = [[2-1, 2-2,    2-3],
 *                        [2-2, origin, origin]] */
template <class Number, class T, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void subtractSingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len);

/* Calculate a - number, and store the result in output
 * This will only calculate the a[pos:pos+len]-number
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 0, len = 4
 *              output = [[1-2, 2-2,    3-2],
 *                        [2-2, origin, origin]] */
template <class T, class Number, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void subtractSingleThread(const Matrix<T> &a,
                          const Number &number,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len);

/* Calculate number * a, and store the result in output
 * This will only calculate the number*a[pos:pos+len]
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 0, len = 4
 *              output = [[2*1, 2*2,    2*3],
 *                        [2*2, origin, origin]] */
template <class Number, class T, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void multiplySingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len);

/* Calculate a / number, and store the result in output
 * This will only calculate the a[pos:pos+len]/number
 * pos: one-demensional starting index of the matrix
 * len: number of elements to be calculated
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 0, len = 4
 *              output = [[1/2, 2/2, 3/2],
 *                        [2/2, origin, origin]] */
template <class T, class Number, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void divideSingleThread(const Matrix<T> &a,
                        const Number &number,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len);

/* Calculate number / a, and store the result in output
 * This will only calculate the number+a[sx:sx+shape.rows][sy:sy+shape+shape.columns]
 * pos: the frist position of matrix a
 * len: length of elements
 * NOTE: a must have the same shape with output
 *       the matrix which will be calculated must in range
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 2
 *              len = 4
 *              output = [[origin, origin, 2/3],
 *                        [2/2,    2/3,    2/4]] */
template <class Number, class T, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
void divideSingleThread(const Number &number,
                        const Matrix<T> &a,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len);

/* Transpose a matrix, and store the result in output
 * This will only get the transposed output[pos:pos+len]
 * pos: the frist position of output
 * len: length of elements
 * NOTE: a must have the same shape with output after transposition
 *       the matrix which will be calculated must in range
 *       &a must not be equal to &output
 * for example: number = 2,
 *              a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              pos = 2
 *              len = 4
 *              output = [[origin, origin],
 *                        [2, 3],
 *                        [3, 4]] */
template <class T>
void transposeSingleThread(const Matrix<T> &a,
                           Matrix<T> &output,
                           const size_t &pos,
                           const size_t &len);

/* Check whether or not rows of matrix are symmetric
 * pos: start position from the first element which will be used
 * len: length of elements
 * NOTE: a must be a square matrix
 *       pos + len must less than or equal to (a.size() - a.rows())/2
 * for example: a = [[1, 2, 3],
 *                   [2, 3, 4],
 *                   [3, 6, 5]]
 *              pos = 0
 *              len = 2
 *              return: true */
template <class T>
bool symmetricSingleThread(const Matrix<T> &a,
                           const size_t &pos,
                           const size_t &len,
                           const double &eps = 1e-100);

/* Check whether or not rows of matrix are antisymmetric
 * pos: start pos from the first element which will be used
 * len: length of elements
 * NOTE: a must be a square matrix
 *       pos + len must less than or equal to (a.size() - a.rows())/2
 * for example: a = [[1,  2, 3],
 *                   [2,  3, 4],
 *                   [3, -4, 5]]
 *              pos = 2 (pos 2's element is 4)
 *              len = 1
 *              return: true */
template <class T>
bool antisymmetricSingleThread(const Matrix<T> &a,
                               const size_t &pos,
                               const size_t &len,
                               const double &eps = 1e-100);

// Those below are the implementations
template <class Number, class T, class O, class>
void numberPowSingleThread(const Number &number,
                           const Matrix<T> &a,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output[i] = static_cast<O>(
            std::pow(static_cast<CommonType>(number), static_cast<CommonType>(a[i])));
    }
}

template <class T, class Number, class O, class>
void powNumberSingleThread(const Matrix<T> &a,
                           const Number &number,
                           Matrix<O> &output,
                           const size_t &pos,
                           const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output[i] = static_cast<O>(
            std::pow(static_cast<CommonType>(a[i]), static_cast<CommonType>(number)));
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
            static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i]) >= -eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            (static_cast<CommonType>(a[i]) >= static_cast<CommonType>(b[i]))) {
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
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            std::fabs(static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i])) > eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) != static_cast<CommonType>(b[i])) {
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
            static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i]) > eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) > static_cast<CommonType>(b[i])) {
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
            (static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i]) < eps ||
             fabs(static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i])) <= eps)) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) <= static_cast<CommonType>(b[i])) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool greaterEqualSingleThread(const Matrix<T1> &a,
                              const Matrix<T2> &b,
                              const size_t &pos,
                              const size_t &len,
                              const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i]) < -eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) < static_cast<CommonType>(b[i])) {
            return false;
        }
    }
    return true;
}

template <class T1, class T2>
bool notEqualSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          const size_t &pos,
                          const size_t &len,
                          const double &eps) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2>;
    for (size_t i = pos; i < pos + len; i++) {
        if (std::is_floating_point_v<CommonType> &&
            std::fabs(static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i])) <= eps) {
            return false;
        }
        if (!std::is_floating_point_v<CommonType> &&
            static_cast<CommonType>(a[i]) == static_cast<CommonType>(b[i])) {
            return false;
        }
    }
    return true;
}

template <class Number, class T, class O, class>
void multiplySingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++)
        output[i] = static_cast<O>(static_cast<CommonType>(a[i]) * static_cast<CommonType>(number));
}

template <class T1, class T2, class O>
void addSingleThread(const Matrix<T1> &a,
                     const Matrix<T2> &b,
                     Matrix<O> &output,
                     const size_t &pos,
                     const size_t &len) {
    assert(a.shape() == b.shape());
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output[i] = static_cast<O>(static_cast<CommonType>(a[i]) + static_cast<CommonType>(b[i]));
    }
}

template <class T1, class T2, class O>
void subtractSingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len) {
    assert(a.shape() == b.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<T1, T2, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output[i] = static_cast<O>(static_cast<CommonType>(a[i]) - static_cast<CommonType>(b[i]));
    }
}

template <class T1, class T2, class O>
void multiplySingleThread(const Matrix<T1> &a,
                          const Matrix<T2> &b,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len) {
    assert(reinterpret_cast<const void *>(&a) != reinterpret_cast<const void *>(&output));
    assert(a.columns() == b.rows());
    assert(a.rows() == output.rows());
    assert(b.columns() == output.columns());
    assert(pos + len <= output.size());
    using CommonType = std::common_type_t<T1, T2, O>;
    size_t i = 0, j = 0;
    for (size_t t = pos; t < pos + len; t++) {
        i                = t / output.columns();
        j                = t % output.columns();
        output.get(i, j) = O();
        for (size_t k = 0; k < a.columns(); k++) {
            // clang-format off
            output.get(i, j) = static_cast<O>(static_cast<CommonType>(output.get(i, j)) +
                                              static_cast<CommonType>(a.get(i, k)) *
                                              static_cast<CommonType>(b.get(k, j)));
            // clang-format on
        }
    }
}

template <class Number, class T, class O, class>
void addSingleThread(const Number &number,
                     const Matrix<T> &a,
                     Matrix<O> &output,
                     const size_t &pos,
                     const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++)
        output[i] = static_cast<O>(static_cast<CommonType>(number) + static_cast<CommonType>(a[i]));
}

template <class Number, class T, class O, class>
void subtractSingleThread(const Number &number,
                          const Matrix<T> &a,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++)
        output[i] = static_cast<O>(static_cast<CommonType>(number) - static_cast<CommonType>(a[i]));
}

template <class T, class Number, class O, class>
void subtractSingleThread(const Matrix<T> &a,
                          const Number &number,
                          Matrix<O> &output,
                          const size_t &pos,
                          const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++)
        output[i] = static_cast<O>(static_cast<CommonType>(a[i]) - static_cast<CommonType>(number));
}

template <class T, class Number, class O, class>
void divideSingleThread(const Matrix<T> &a,
                        const Number &number,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++)
        output[i] = static_cast<O>(static_cast<CommonType>(a[i]) / static_cast<CommonType>(number));
}

template <class Number, class T, class O, class>
void divideSingleThread(const Number &number,
                        const Matrix<T> &a,
                        Matrix<O> &output,
                        const size_t &pos,
                        const size_t &len) {
    assert(a.shape() == output.shape());
    assert(pos + len <= a.size());
    using CommonType = std::common_type_t<Number, T, O>;
    for (size_t i = pos; i < pos + len; i++) {
        output[i] = static_cast<O>(static_cast<CommonType>(number) / static_cast<CommonType>(a[i]));
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
