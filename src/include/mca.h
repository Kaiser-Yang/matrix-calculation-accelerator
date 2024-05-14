#ifndef MCA_PRIVATE_H
#define MCA_PRIVATE_H

#include <thread>

#include "thread_pool.h"

namespace mca {
// forward declaration to remove circular dependency
template <class ELEMENT_TYPE>
class Matrix;

// Initialize the mca, before using mca, you must call init
// If you don't call init, mca will run in single thread mode
// threadNum is how many threads will be used when calculating
// limit is the minimal quantity of a thread's calculation
// eps is the epsilon when comparing matrices whose elements' types are floating number
extern void init(const size_t &threadNum = std::thread::hardware_concurrency() - 1,
                 const size_t &limit     = 623,
                 const double &eps       = 1e-100);

// Set how many threads will be used when calculating
extern void setThreadNum(const size_t &threadNum);

// Set the minimal quantity of a thread's calculation
// Make sure every sub-thread's calculation is no less than limit
// When the rest part is less than limit, the main thread will calculate the rest
// NOTE: if you want to calculate with single thread, you can set the limit with
//       std::numeric_limits<size_t>::max()
extern void setLimit(const size_t &limit);

// set the epsilon used for comparing floating numbers
extern void setEpsilon(const double &eps);

// return current thread number
extern size_t threadNum();

// return current limit
extern size_t limit();

// return current epsilon
extern double epsilon();

// return trhead pool object, this should not called by the usrs
// this is for developers
extern ThreadPool &threadPool();

// Check if matrix a and matrix b are equal using multi-thread
// return false when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator==(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if matrix a and matrix b are not equal using multi-thread
// return true when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are less than b's using multi-thread
// return false when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator<(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are less or equal than b's using multi-thread
// return false when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are greater than b's using multi-thread
// return false when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator>(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are greater or equal than b's using multi-thread
// return false when a's shape is not same with b's shape
// NOTE: before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a + b using multi-thread
// return the result of a + b
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a - b using multi-thread
// return the result of a - b
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a * b using multi-thread
// return the result of a * b
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a + number using multi-thread
// return the result of a + number
// this is same with a + Matrix(a.getShape(), number)
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1+1, 2+1],
//                       [3+1, 4+1]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a, const Number &number);

// Calculate number + a using multi-thread
// return the result of number + a
// this is same with Matrix(a.getShape(), number) + a
// for example: number = 1
//              a = [[1, 2],
//                   [3, 4]]
//              return: [[1+1, 1+2],
//                       [1+3, 1+4]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator+(const Number &number, const Matrix<T> &a);

// Calculate a - number using multi-thread
// return the result of a - number
// this is same with a - Matrix(a.getShape(), number)
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1-1, 2-1],
//                       [3-1, 4-1]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a, const Number &number);

// Calculate number - a using multi-thread
// return the result of number - a
// this is same with Matrix(a.getShape(), number) - a
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1-1, 1-2],
//                       [1-3, 1-4]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator-(const Number &number, const Matrix<T> &a);

// Calculate a * number using multi-thread
// return the result of a * number
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1*1, 2*1],
//                       [3*1, 4*1]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a, const Number &number);

// Calculate number * a using multi-thread
// return the result of number * a
// for example: number = 1
//              a = [[1, 2],
//                   [3, 4]]
//              return: [[1*1, 1*2],
//                       [1*3, 1*4]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator*(const Number &number, const Matrix<T> &a);

// Calculate a / number using multi-thread
// return the result of a / number
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1/1, 2/1],
//                       [3/1, 4/1]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a, const Number &number);

// Calculate number / a using multi-thread
// return the result of number / a
// this is same with Matrix(a.getShape(), number) / a
// for example: a = [[1, 2],
//                   [3, 4]]
//              number = 1
//              return: [[1/1, 1/2],
//                       [1/3, 1/4]]
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator/(const Number &number, const Matrix<T> &a);

// Calculate a += b using multi-thread, the result will be stored in a
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
void operator+=(Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a -= b using multi-thread, the result will be stored in a
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
void operator-=(Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a *= b using multi-thread, the result will be stored in a
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
void operator*=(Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a /= b using multi-thread, the result will be stored in a
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
void operator/=(Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a += number using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
void operator+=(Matrix<T> &a, const Number &number);

// Calculate number += a using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
void operator+=(const Number &number, Matrix<T> &a);

// Calculate a -= number using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
void operator-=(Matrix<T> &a, const Number &number);

// Calculate number -= a using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
void operator-=(const Number &number, Matrix<T> &a);

// Calculate a *= number using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
void operator*=(Matrix<T> &a, const Number &number);

// Calculate number *= a using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
void operator*=(const Number &number, Matrix<T> &a);

// Calculate a /= number using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T, class Number>
void operator/=(Matrix<T> &a, const Number &number);

// Calculate number /= a using multi-thread, the result will be stored in a
// NOTE: the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class Number, class T>
void operator/=(const Number &number, Matrix<T> &a);

// Those below are the implementations
// TODO
template <class T1, class T2>
bool operator==(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
bool operator<(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
bool operator>(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b) {}

// TODO
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b) {}

// TODO
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator+(const Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator+(const Number &number, const Matrix<T> &a) {}
// TODO
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator-(const Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator-(const Number &number, const Matrix<T> &a) {}
// TODO
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a, const Number &number) {}
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator*(const Number &number, const Matrix<T> &a) {}
// TODO
template <class T, class Number>
Matrix<std::common_type_t<T, Number>> operator/(const Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
Matrix<std::common_type_t<T, Number>> operator/(const Number &number, const Matrix<T> &a) {}

// TODO
template <class T1, class T2>
void operator+=(Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
void operator-=(Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
void operator*=(Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T1, class T2>
void operator/=(Matrix<T1> &a, const Matrix<T2> &b) {}
// TODO
template <class T, class Number>
void operator+=(Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
void operator+=(const Number &number, Matrix<T> &a) {}
// TODO
template <class T, class Number>
void operator-=(Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
void operator-=(const Number &number, Matrix<T> &a) {}
// TODO
template <class T, class Number>
void operator*=(Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
void operator*=(const Number &number, Matrix<T> &a) {}
// TODO
template <class T, class Number>
void operator/=(Matrix<T> &a, const Number &number) {}
// TODO
template <class Number, class T>
void operator/=(const Number &number, Matrix<T> &a) {}

inline std::pair<size_t, size_t> threadCalculationTaskNum(const size_t &total) {
    size_t threadCalculation = std::max(total / (threadNum() + 1), limit());
    size_t taskNum           = total / threadCalculation;
    if (total % threadCalculation > 0) { taskNum++; }
    return {threadCalculation, taskNum};
}
}  // namespace mca
#endif
