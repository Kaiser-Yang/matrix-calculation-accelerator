# mca::Matrix
```c++
/* Defined in header file <mca/matrix.h> */
template <class T> class Matrix;
```
## Member types
|                                       |   |
| -                                     | - |
| <nobr>`value_type`</nobr>             | <nobr>`T`</nobr> |
| <nobr>`size_type`</nobr>              | <nobr>`std::size_t`</nobr> |
| <nobr>`difference_type`</nobr>        | <nobr>`std::ptrdiff_t`</nobr> |
| <nobr>`reference`</nobr>              | <nobr>`T&`</nobr> |
| <nobr>`const_reference`</nobr>        | <nobr>`const T&`</nobr> |
| <nobr>`pointer`</nobr>                | <nobr>`T*`</nobr> |
| <nobr>`const_pointer`</nobr>          | <nobr>`const T*`</nobr> |
| <nobr>`iterator`</nobr>               | <nobr>`T*`</nobr> |
| <nobr>`const_iterator`</nobr>         | <nobr>`const T*`</nobr> |
| <nobr>`reverse_iterator`</nobr>       | <nobr>`std::reverse_iterator<iterator>`</nobr> |
| <nobr>`const_reverse_iterator`</nobr> | <nobr>`std::reverse_iterator<const_iterator>`</nobr> |

## Member functions
### Constructors
|                                                                                             |   |
| -                                                                                           | - |
| <nobr>`Matrix()`</nobr>                                                                     | Construct an empty matrix. |
| <nobr>`Matrix(const Shape &shape, const _IdentityMatrix &)`</nobr>                          | Construct an identity matrix with the given shape. |
| <nobr>`Matrix(const std::initializer_list<std::initializer_list<value_type>> &init)`</nobr> | Construct a matrix from a list of lists. |
| <nobr>`Matrix(const std::vector<std::vector<value_type>> &init)`</nobr>                     | Construct a matrix from a vector of vectors. |
| <nobr>`Matrix(const Shape &shape, const_pointer data, const size_type &len)`</nobr>         | Construct a matrix from a pointer. When `len` is less than `shape.size()`, the rest part will be filled with `value_type()` |
| <nobr>`Matrix(const Shape &shape, const value_type (&array)[N])`</nobr>                     | Construct a matrix from an array. When `N` is less than `shape.size()`, the rest part will be filled with `value_type()` |
| <nobr>`Matrix(const Shape &shape, std::array<value_type, N> &array)`</nobr>                 | Construct a matrix from a `std::array`. When `N` is less than `shape.size()`, the rest part will be filled with `value_type()` |
| <nobr>`Matrix(const Shape &shape, const_reference defaultValue = value_type())`</nobr>      | Construct a matrix with the given shape and default value. |
| <nobr>`Matrix(const _Diag<Container> &diag)`</nobr>                                         | Construct a diagonal matrix from a container. |
| <nobr>`Matrix(const Matrix<T1> &other)`</nobr>                                              | Copy constructor. When `T1` is not the same as `T`, the elements will be converted to `T` by using `static_cast`. |
| <nobr>`Matrix(Matrix &&other) noexcept`</nobr>                                              | Move constructor which only supports the matrices with same `value_type`. |

[The examples of constructing a matrix.](../../../example/matrix_construction.cpp)

### Operators
|                                                                               |   |
| -                                                                             | - |
| <nobr>`Matrix &operator=(Matrix &&other) noexcept`</nobr>                     | Move assignment operator which only supports the matrices with same `value_type`. |
| <nobr>`Matrix &operator=(const Matrix<T1> &other)`</nobr>                     | Copy assignment operator. When `T1` is not the same as `T`, the elements will be converted to `T` by using `static_cast`. |
| <nobr>`[const_]reference operator[](const size_type &pos) [const]`</nobr>     | Get the element at pos, the elements are numbered sequentially from left to right and top to bottom. |

This part has not been finished yet. Add some examples.

### Iterators
|                                                                   |   |
| -                                                                 | - |
| <nobr>`[const_]iterator begin() [const] noexcept`</nobr>          | Return an iterator to the beginning. |
| <nobr>`[const_]iterator end() [const] noexcept`</nobr>            | Return an iterator to the end. |
| <nobr>`const_iterator cbegin() const noexcept`</nobr>             | Return a const iterator to the beginning. |
| <nobr>`const_iterator cend() const noexcept`</nobr>               | Return a const iterator to the end. |
| <nobr>`[const_]reverse_iterator rbegin() [const] noexcept`</nobr> | Return a reverse iterator to the beginning. |
| <nobr>`[const_]reverse_iterator rend() [const] noexcept`</nobr>   | Return a reverse iterator to the end. |
| <nobr>`const_reverse_iterator crbegin() const noexcept`</nobr>    | Return a const reverse iterator to the beginning. |
| <nobr>`const_reverse_iterator crend() const noexcept`</nobr>      | Return a const reverse iterator to the end. |

This part has not been finished yet. Add some examples.

### Other
|                                                                                      |   |
| -                                                                                    | - |
| <nobr>`[const_]reference get(const size_type &i, const size_type &j) [const]`</nobr> | Get the element at (i, j). |
| <nobr>`[const_]pointer data() [const] noexcept`</nobr>                               | Get the data pointer. |
| <nobr>`size_type rows() const noexcept`</nobr>                                       | Get the number of rows. |
| <nobr>`size_type cols() const noexcept`</nobr>                                       | Get the number of columns. |
| <nobr>`size_type size() const noexcept`</nobr>                                       | Get the number of elements. |
| <nobr>`Shape shape() const noexcept`</nobr>                                          | Get the shape of the matrix. |
| <nobr>`void reshape(const Shape &shape) noexcept`</nobr>                             | Reshape the matrix. The size of the new shape must be same with the old one. |
| <nobr>`void fill(const_reference value, const size_type &pos = 0)`</nobr>            | Fill the matrix with the given value from the given position. |
| <nobr>`Matrix numberPow(const Number &number)`</nobr>                                | Return a matrix whose elements are the `number`s to the original element-th power. |
| <nobr>`Matrix powNumber(const Number &number)`</nobr>                                | Return a matrix whose elements are the original elements to the `number`-th power. |
| <nobr>`Matrix pow(const size_type &exponent) const`</nobr>                           | Return a result of the matrix raised to the power of `exponent`. The original matrix must be a square matrix. |
| <nobr>`Matrix transpose() const`</nobr>                                              | Return the transpose of the matrix. |
| <nobr>`bool square() const noexcept`</nobr>                                          | Check if the matrix is a square matrix. |
| <nobr>`bool symmetric() const`</nobr>                                                | Check if the matrix is symmetric. |
| <nobr>`bool antisymmetric() const`</nobr>                                            | Check if the matrix is antisymmetric. |
| <nobr>`[const_]reference front() [const]`</nobr>                                     | Return the first element of the matrix, the size must be greater than `0` |
| <nobr>`[const_]reference back() [const]`</nobr>                                      | Return the last element of the matrix, the size must be greater than `0` |
| <nobr>`bool empty() const noexcept`</nobr>                                           | Check if the matrix is empty. |
| <nobr>`void swap(Matrix &other) noexcept`</nobr>                                     | Swap the matrix with another matrix. Only the matrices with same `value_type` can be swapped. |

This part has not been finished yet. Add some examples.

## Non-member functions
See [`mca`](mca.md) for more information.

## Helper classes
|                                             |   |
| -                                           | - |
| [`mca::Shape`](shape.md)                    | A helper class for matrices' shape |
| [`mca::_Diag`](diag.md)                     | A helper class for diagonal matrices. |
| [`mca::_IdentityMatrix`](identityMatrix.md) | A helper class for identity matrices. |

[Back to the `Get started`](buildAndInstall.md)

[Next: `mca::Shape`](shape.md)

[Back to the index](index.md)
