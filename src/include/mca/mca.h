#ifndef MCA_MCA_H
#define MCA_MCA_H

#include <future>
#include <thread>
#include <type_traits>
#include <vector>

#include "__mca_internal/matrix_declaration.h"
#include "__mca_internal/single_thread_matrix_calculation.h"
#include "__mca_internal/thread_pool.h"
#include "__mca_internal/utility.h"
#include "identity_matrix.h"
#include "shape.h"

namespace mca {
using size_type = std::size_t;
/* Initialize the mca, before using mca, you must call init
 * If you don't call init, mca will run in single thread mode
 * threadNum is how many threads will be used when calculating
 * limit is the minimal quantity of a thread's calculation
 * eps is the epsilon when comparing matrices whose elements' types are floating number */
extern void init(const size_type &threadNum = std::thread::hardware_concurrency() - 1,
                 const size_type &limit     = 623,
                 const double &eps          = 1e-100);

/* Set how many threads will be used when calculating */
extern void setThreadNum(const size_type &threadNum);

/* Set the minimal quantity of a thread's calculation
 * Make sure every sub-thread's calculation is no less than limit
 * When the rest part is less than limit, the main thread will calculate the rest
 * NOTE: if you want to calculate with single thread, you can set the limit with
 *       std::numeric_limits<size_type>::max() */
extern void setLimit(const size_type &limit);

/* set the epsilon used for comparing floating numbers */
extern void setEpsilon(const double &eps);

/* return current thread number */
extern size_type threadNum();

/* return current limit */
extern size_type limit();

/* return current epsilon */
extern double epsilon();

/* return trhead pool object, this should not called by the usrs
 * this is for developers */
extern ThreadPool &threadPool();
inline std::pair<size_type, size_type> threadCalculationTaskNum(const size_type &total);

/* Check if matrix a and matrix b are equal using multi-thread
 * return false when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator==(const Matrix<T1> &a, const Matrix<T2> &b);

/* Check if matrix a and matrix b are not equal using multi-thread
 * return true when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b);

/* Check if all the elements of a are less than b's using multi-thread
 * return false when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator<(const Matrix<T1> &a, const Matrix<T2> &b);

/* Check if all the elements of a are less or equal than b's using multi-thread
 * return false when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b);

/* Check if all the elements of a are greater than b's using multi-thread
 * return false when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator>(const Matrix<T1> &a, const Matrix<T2> &b);

/* Check if all the elements of a are greater or equal than b's using multi-thread
 * return false when a's shape is not same with b's shape
 * NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
 *       if they are floating number, the eps will be used to compare
 *       the default value of eps is 1e-100 */
template <class T1, class T2>
bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a + b using multi-thread
 * return the result of a + b
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a - b using multi-thread
 * return the result of a - b
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a * b using multi-thread
 * return the result of a * b
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a + number using multi-thread
 * return the result of a + number
 * this is same with a + Matrix(a.shape(), number)
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1+1, 2+1],
 *                       [3+1, 4+1]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a, const Number &number);

/* Calculate number + a using multi-thread
 * return the result of number + a
 * this is same with Matrix(a.shape(), number) + a
 * for example: number = 1
 *              a = [[1, 2],
 *                   [3, 4]]
 *              return: [[1+1, 1+2],
 *                       [1+3, 1+4]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
inline Matrix<std::common_type_t<T, Number>> operator+(const Number &number, const Matrix<T> &a);

/* Calculate a - number using multi-thread
 * return the result of a - number
 * this is same with a - Matrix(a.shape(), number)
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1-1, 2-1],
 *                       [3-1, 4-1]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a, const Number &number);

/* Calculate number - a using multi-thread
 * return the result of number - a
 * this is same with Matrix(a.shape(), number) - a
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1-1, 1-2],
 *                       [1-3, 1-4]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator-(const Number &number, const Matrix<T> &a);

/* Calculate a * number using multi-thread
 * return the result of a * number
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1*1, 2*1],
 *                       [3*1, 4*1]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
inline Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a, const Number &number);

/* Calculate number * a using multi-thread
 * return the result of number * a
 * for example: number = 1
 *              a = [[1, 2],
 *                   [3, 4]]
 *              return: [[1*1, 1*2],
 *                       [1*3, 1*4]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator*(const Number &number, const Matrix<T> &a);

/* Calculate a / number using multi-thread
 * return the result of a / number
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1/1, 2/1],
 *                       [3/1, 4/1]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a, const Number &number);

/* Calculate number / a using multi-thread
 * return the result of number / a
 * this is same with Matrix(a.shape(), number) / a
 * for example: a = [[1, 2],
 *                   [3, 4]]
 *              number = 1
 *              return: [[1/1, 1/2],
 *                       [1/3, 1/4]]
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
Matrix<std::common_type_t<T, Number>> operator/(const Number &number, const Matrix<T> &a);

/* Calculate a += b using multi-thread, the result will be stored in a
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
void operator+=(Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a -= b using multi-thread, the result will be stored in a
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
void operator-=(Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a *= b using multi-thread, the result will be stored in a
 * NOTE: a's shape must be same with b'shape
 *       the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T1, class T2>
void operator*=(Matrix<T1> &a, const Matrix<T2> &b);

/* Calculate a += number using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator+=(Matrix<T> &a, const Number &number);

/* Calculate number += a using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
inline void operator+=(const Number &number, Matrix<T> &a);

/* Calculate a -= number using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator-=(Matrix<T> &a, const Number &number);

/* Calculate number -= a using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator-=(const Number &number, Matrix<T> &a);

/* Calculate a *= number using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
inline void operator*=(Matrix<T> &a, const Number &number);

/* Calculate number *= a using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator*=(const Number &number, Matrix<T> &a);

/* Calculate a /= number using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class T, class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator/=(Matrix<T> &a, const Number &number);

/* Calculate number /= a using multi-thread, the result will be stored in a
 * NOTE: the calculation will first calculate as std::common_type<T1, T2>
 *       then use static_cast<T1> */
template <class Number, class T, class = std::enable_if_t<!is_matrix_v<Number>>>
void operator/=(const Number &number, Matrix<T> &a);

/* Transpose a in place using multi-thread
 * for example: a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              transpose(a)
 *              a: [[1, 2],
 *                  [2, 3],
 *                  [3, 4]] */
template <class T>
void transpose(Matrix<T> &a);

/* Store the transposed matrix of a in output using multi-thread
 * NOTE: output must have the same shape with the current matrix after transposition
 *       If O and T are not same, all the elements will first be cast to
 *       std::common_type<O, T>, after calculation they will be cast into O
 *       by using static_cast
 * for example: a = [[1, 2, 3],
 *                   [2, 3, 4]]
 *              transpose(a, output)
 *              a: [[1, 2, 3],
 *                  [2, 3, 4]]
 *              output: [[1, 2],
 *                       [2, 3],
 *                       [3, 4]] */
template <class T, class O>
void transpose(const Matrix<T> &a, Matrix<O> &output);

template <class T1, class T2>
bool operator==(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return false; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return equalSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return equalSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = equalSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result &= item.get(); }
    return result;
}

template <class T1, class T2>
bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return true; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return notEqualSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return notEqualSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = notEqualSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result |= item.get(); }
    return result;
}

template <class T1, class T2>
bool operator<(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return false; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return lessSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return lessSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = lessSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result &= item.get(); }
    return result;
}

template <class T1, class T2>
bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return false; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return lessEqualSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return lessEqualSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = lessEqualSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result &= item.get(); }
    return result;
}

template <class T1, class T2>
bool operator>(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return false; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return greaterSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return greaterSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = greaterSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result &= item.get(); }
    return result;
}

template <class T1, class T2>
bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b) {
    if (a.shape() != b.shape()) { return false; }
    if (threadNum() == 0 || limit() >= a.size()) {
        return greaterEqualSingleThread(a, b, 0, a.size(), epsilon());
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<bool>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() -> bool {
                return greaterEqualSingleThread(a, b, start, len, epsilon());
            });
    }
    bool result = greaterEqualSingleThread(
        a, b, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first, epsilon());
    for (auto &item : returnValue) { result &= item.get(); }
    return result;
}

template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.shape() == b.shape());
    using CommonType = std::common_type_t<T1, T2>;
    Matrix<CommonType> result(a.shape());
    if (threadNum() == 0 || limit() >= a.size()) {
        addSingleThread(a, b, result, 0, a.size());
        return result;
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &b, len = res.first]() {
                addSingleThread(a, b, result, start, len);
            });
    }
    addSingleThread(
        a, b, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.shape() == b.shape());
    using CommonType = std::common_type_t<T1, T2>;
    Matrix<CommonType> result(a.shape());
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(a, b, result, 0, a.size());
        return result;
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &b, len = res.first]() {
                subtractSingleThread(a, b, result, start, len);
            });
    }
    subtractSingleThread(
        a, b, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.columns() == b.rows());
    using CommonType = std::common_type_t<T1, T2>;
    Matrix<CommonType> result(Shape{a.rows(), b.columns()});
    if (threadNum() == 0 || limit() >= result.size()) {
        multiplySingleThread(a, b, result, 0, result.size());
        return result;
    }
    auto res = threadCalculationTaskNum(result.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &b, len = res.first]() {
                multiplySingleThread(a, b, result, start, len);
            });
    }
    multiplySingleThread(
        a, b, result, (res.second - 1) * res.first, result.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T, class Number, class>
Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a, const Number &number) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        addSingleThread(number, a, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                addSingleThread(number, a, result, start, len);
            });
    }
    // let main thread calculate too
    addSingleThread(
        number, a, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class Number, class T, class>
inline Matrix<std::common_type_t<T, Number>> operator+(const Number &number, const Matrix<T> &a) {
    return a + number;
}

template <class T, class Number, class>
Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a, const Number &number) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(a, number, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                subtractSingleThread(a, number, result, start, len);
            });
    }
    // let main thread calculate too
    subtractSingleThread(
        a, number, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class Number, class T, class>
Matrix<std::common_type_t<T, Number>> operator-(const Number &number, const Matrix<T> &a) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(number, a, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                subtractSingleThread(number, a, result, start, len);
            });
    }
    // let main thread calculate too
    subtractSingleThread(
        number, a, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T, class Number, class>
inline Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a, const Number &number) {
    return number * a;
}

template <class Number, class T, class>
Matrix<std::common_type_t<T, Number>> operator*(const Number &number, const Matrix<T> &a) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        multiplySingleThread(number, a, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                multiplySingleThread(number, a, result, start, len);
            });
    }
    // let main thread calculate too
    multiplySingleThread(
        number, a, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T, class Number, class>
Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a, const Number &number) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        divideSingleThread(a, number, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                divideSingleThread(a, number, result, start, len);
            });
    }
    // let main thread calculate too
    divideSingleThread(
        a, number, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class Number, class T, class>
Matrix<std::common_type_t<T, Number>> operator/(const Number &number, const Matrix<T> &a) {
    using CommonType = std::common_type_t<T, Number>;
    Matrix<CommonType> result(a.shape());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        divideSingleThread(number, a, result, 0, a.size());
        return result;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &number, len = res.first]() {
                divideSingleThread(number, a, result, start, len);
            });
    }
    // let main thread calculate too
    divideSingleThread(
        number, a, result, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return result;
}

template <class T1, class T2>
void operator+=(Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.shape() == b.shape());
    if (threadNum() == 0 || limit() >= a.size()) {
        addSingleThread(a, b, a, 0, a.size());
        return;
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() {
            addSingleThread(a, b, a, start, len);
        });
    }
    addSingleThread(a, b, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
}

template <class T1, class T2>
void operator-=(Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.shape() == b.shape());
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(a, b, a, 0, a.size());
        return;
    }
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask([start = i * res.first, &a, &b, len = res.first]() {
            subtractSingleThread(a, b, a, start, len);
        });
    }
    subtractSingleThread(
        a, b, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
}

template <class T1, class T2>
void operator*=(Matrix<T1> &a, const Matrix<T2> &b) {
    assert(a.columns() == b.rows());
    Matrix<T1> result(Shape{a.rows(), b.columns()}, IdentityMatrix());
    if (threadNum() == 0 || limit() >= result.size()) {
        multiplySingleThread(a, b, result, 0, result.size());
        a = std::move(result);
        return;
    }
    auto res = threadCalculationTaskNum(result.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&result, start = i * res.first, &a, &b, len = res.first]() {
                multiplySingleThread(a, b, result, start, len);
            });
    }
    multiplySingleThread(
        a, b, result, (res.second - 1) * res.first, result.size() - (res.second - 1) * res.first);
    for (auto &item : returnValue) { item.get(); }
    a = std::move(result);
}

template <class T, class Number, class>
void operator+=(Matrix<T> &a, const Number &number) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        addSingleThread(number, a, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                addSingleThread(number, a, a, start, len);
            });
    }
    // let main thread calculate too
    addSingleThread(
        number, a, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class Number, class T, class>
inline void operator+=(const Number &number, Matrix<T> &a) {
    a += number;
}

template <class T, class Number, class>
void operator-=(Matrix<T> &a, const Number &number) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(a, number, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                subtractSingleThread(a, number, a, start, len);
            });
    }
    // let main thread calculate too
    subtractSingleThread(
        a, number, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return;
}

template <class Number, class T, class>
void operator-=(const Number &number, Matrix<T> &a) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        subtractSingleThread(number, a, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                subtractSingleThread(number, a, a, start, len);
            });
    }
    // let main thread calculate too
    subtractSingleThread(
        number, a, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class T, class Number, class>
inline void operator*=(Matrix<T> &a, const Number &number) {
    number *= a;
}

template <class Number, class T, class>
void operator*=(const Number &number, Matrix<T> &a) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        multiplySingleThread(number, a, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                multiplySingleThread(number, a, a, start, len);
            });
    }
    // let main thread calculate too
    multiplySingleThread(
        number, a, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return;
}

template <class T, class Number, class>
void operator/=(Matrix<T> &a, const Number &number) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        divideSingleThread(a, number, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                divideSingleThread(a, number, a, start, len);
            });
    }
    // let main thread calculate too
    divideSingleThread(
        a, number, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class Number, class T, class>
void operator/=(const Number &number, Matrix<T> &a) {
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        divideSingleThread(number, a, a, 0, a.size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([start = i * res.first, &a, &number, len = res.first]() {
                divideSingleThread(number, a, a, start, len);
            });
    }
    // let main thread calculate too
    divideSingleThread(
        number, a, a, (res.second - 1) * res.first, a.size() - (res.second - 1) * res.first);
    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
    return;
}

template <class T>
void transpose(Matrix<T> &a) {
    Matrix<T> output(Shape{a.columns(), a.rows()});
    transpose(a, output);
    a = std::move(output);
}

template <class T, class O>
void transpose(const Matrix<T> &a, Matrix<O> &output) {
    assert(a.rows() == output.columns());
    assert(a.columns() == output.rows());
    // single mode
    if (threadNum() == 0 || limit() >= a.size()) {
        transposeSingleThread(a, output, 0, a.size());
        return;
    }

    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(a.size());

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);

    // assign task for every sub-thread
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([&a, start = i * res.first, len = res.first, &output]() {
                transposeSingleThread(a, output, start, len);
            });
    }

    // let main thread calculate took
    transposeSingleThread(
        a, output, (res.second - 1) * res.first, (a.size() - (res.second - 1) * res.first));

    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

inline std::pair<size_type, size_type> threadCalculationTaskNum(const size_type &total) {
    size_type threadCalculation = std::max(total / (threadNum() + 1), limit());
    size_type taskNum           = total / threadCalculation;
    if (total % threadCalculation > 0) { taskNum++; }
    return {threadCalculation, taskNum};
}
}  // namespace mca
#endif
