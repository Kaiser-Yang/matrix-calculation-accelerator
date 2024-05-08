#ifndef MCA_PRIVATE_H
#define MCA_PRIVATE_H

#include "matrix.h"

namespace mca {

// the eps will be used when comparing matrices whose elements are floating numbers
extern double eps;
// Check if matrix a and matrix b are equal using multi-thread
// NOTE: a's shape must be same with b'shape
//       before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator==(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if matrix a and matrix b are not equal using multi-thread
// NOTE: a's shape must be same with b'shape
//       before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are less than b's using multi-thread
// NOTE: a's shape must be same with b'shape
//       before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator<(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are less or equal than b's using multi-thread
// NOTE: a's shape must be same with b'shape
//       before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are greater than b's using multi-thread
// NOTE: a's shape must be same with b'shape
//       before comparison the elements will be converted to std::common_type<T1, T2>
//       if they are floating number, the eps will be used to compare
//       the default value of eps is 1e-100
template <class T1, class T2>
bool operator>(const Matrix<T1> &a, const Matrix<T2> &b);

// Check if all the elements of a are greater or equal than b's using multi-thread
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a + b using multi-thread
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator+(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a - b using multi-thread
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator-(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a * b using multi-thread
// NOTE: a's shape must be same with b'shape
//       the calculation will first calculate as std::common_type<T1, T2>
//       then use static_cast<T1>
template <class T1, class T2>
Matrix<std::common_type_t<T1, T2>> operator*(const Matrix<T1> &a, const Matrix<T2> &b);

// Calculate a + number using multi-thread
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
Matrix<std::common_type_t<T, Number>> operator*(const Matrix<T> &a,
                                                // TODO
                                                const Number &number) {}
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
}  // namespace mca
#endif
