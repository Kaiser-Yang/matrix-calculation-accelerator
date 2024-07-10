# Matrix calculation accelerator
All the methods are defined in `mca.h`.

|                                                                                            |   |
| -                                                                                          | - |
| <nobr>`bool operator==(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                   | Return `true` if the two matrices are equal, `false` otherwise. |
| <nobr>`bool operator!=(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                   | Return `true` if the two matrices are not equal, `false` otherwise. |
| <nobr>`bool operator<(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                    | Return `true` if all elements of the first matrix is less than the second matrix, `false` otherwise. |
| <nobr>`bool operator<=(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                   | Return `true` if all elements of the first matrix is less than or equal to the second matrix, `false` otherwise. |
| <nobr>`bool operator>(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                    | Return `true` if all elements of the first matrix is greater than the second matrix, `false` otherwise. |
| <nobr>`bool operator>=(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                   | Return `true` if all elements of the first matrix is greater than or equal to the second matrix, `false` otherwise. |
| <nobr>`Matrix operator+(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                  | Return the sum of the two matrices. The `value_type` of the return value is `std::common_type_t<T1, T2>`. |
| <nobr>`Matrix operator-(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                  | Return the difference of the two matrices. The `value_type` of the return value is `std::common_type_t<T1, T2>`. |
| <nobr>`Matrix operator*(const Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                  | Return the product of the two matrices. The `value_type` of the return value is `std::common_type_t<T1, T2>`. |
| <nobr>`Matrix operator+(const Matrix<T> &a, const Number &number)`</nobr>                  | Return `a + Matrix<Number>(a.shape(), number)`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator+(const Number &number, const Matrix<T> &a)`</nobr>                  | Return `a + Matrix<Number>(a.shape(), number)`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator-(const Matrix<T> &a, const Number &number)`</nobr>                  | Return `a - Matrix<Number>(a.shape(), number)`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator-(const Number &number, const Matrix<T> &a)`</nobr>                  | Return `Matrix<Number>(a.shape(), number) - a`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator*(const Matrix<T> &a, const Number &number)`</nobr>                  | Return a matrix whose elements are `a`'s multiplied by `number`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator*(const Number &number, const Matrix<T> &a)`</nobr>                  | Return a matrix whose elements are `a`'s multiplied by `number`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator/(const Matrix<T> &a, const Number &number)`</nobr>                  | Return a matrix whose elements are `a`'s divided by `number`. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`Matrix operator/(const Number &number, const Matrix<T> &a)`</nobr>                  | Return a matrix whose elements are `number` divided by `a`'s elements. The `value_type` of the return value is `std::common_type_t<T, Number>`. |
| <nobr>`void operator+=(Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                         | Self matrix addition |
| <nobr>`void operator-=(Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                         | Self matrix subtraction |
| <nobr>`void operator*=(Matrix<T1> &a, const Matrix<T2> &b)`</nobr>                         | Self matrix multiplication |
| <nobr>`void operator+=(Matrix<T> &a, const Number &number)`</nobr>                         | Same with `a += Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator+=(const Number &number, Matrix<T> &a)`</nobr>                         | Same with `a += Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator-=(Matrix<T> &a, const Number &number)`</nobr>                         | Same with `a -= Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator-=(const Number &number, Matrix<T> &a)`</nobr>                         | Same with `a = Matrix<Number>(a.shape, number) - a`. |
| <nobr>`void operator*=(Matrix<T> &a, const Number &number)`</nobr>                         | Same with `a *= Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator*=(const Number &number, Matrix<T> &a)`</nobr>                         | Same with `a *= Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator/=(Matrix<T> &a, const Number &number)`</nobr>                         | Same with `a /= Matrix<Number>(a.shape, number)`. |
| <nobr>`void operator/=(const Number &number, Matrix<T> &a)`</nobr>                         | Same with `a = Matrix<Number>(a.shape, number) / a`. |
| <nobr>`void transpose(Matrix<T> &a)`</nobr>                                                | Tranpose a matrix. |
| <nobr>`void transpose(const Matrix<T> &a, Matrix<O> &output)`</nobr>                       | Tranpose a matrix, but store the result into `output`. |
| <nobr>`void pow(Matrix<T> &a, const size_type &exponent)`</nobr>                           | Raise a matrix to the power of `exponent`. |
| <nobr>`void pow(const Matrix<T> &a, const size_type &exponent, Matrix<O> &output)`</nobr>  | Raise a matrix to the power of `exponent`, but store the result into `output`. |
| <nobr>`void numberPow(const Number &number, Matrix<T> &a)`</nobr>                          | `a`'s elements will be the `number`'s to the original element-th power. |
| <nobr>`void numberPow(const Number &number, Matrix<T> &a, Matrix<O> &output)`</nobr>       | `output`'s elements will be the `number`'s to the `a`'s element-th power. |
| <nobr>`void powNumber(Matrix<T> &a, const Number &number)`</nobr>                          | `a`'s elements will be the original to the `number`-th power. |
| <nobr>`void powNumber(const Matrix<T> &a, const Number &number, Matrix<O> &output)`</nobr> | `output`'s elements will be the `a`'s elements to the `nubmer`-th power. |

[The examples of `mca`.](../../../example/mca_examples.cpp)

[Back to the `mca::Matrix`](matrix.md)

[Back to the `mca::_IdentityMatrix`](identityMatrix.md)

[Next: `mca configurations`](mcaConfig.md)

[Back to the index](index.md)
