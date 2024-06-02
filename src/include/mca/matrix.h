#ifndef MCA_MATRIX_H
#define MCA_MATRIX_H

#include <cassert>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "__mca_internal/matrix_declaration.h"
#include "__mca_internal/single_thread_matrix_calculation.h"
#include "diag.h"
#include "identity_matrix.h"
#include "mca.h"
#include "shape.h"

namespace mca {
template <class T>
class Matrix {
public:
    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type &;
    using const_reference        = const value_type &;
    using pointer                = value_type *;
    using const_pointer          = const value_type *;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /* Construct an empty matrix */
    inline Matrix() = default;

    /* Construct an identity matrix
     * NOTE: the diagonal elements will be constructed by value_type(1) */
    explicit Matrix(const Shape &shape, const IdentityMatrix &);

    /* Construct a matrix from a initializer_list
     * You can use this like Matrix<int>({{1, 2}, {3, 4}}) */
    explicit Matrix(const std::initializer_list<std::initializer_list<value_type>> &init);

    /* Construct a matrix from a vector */
    explicit Matrix(const std::vector<std::vector<value_type>> &init);

    /* Construct a matrix from a pointer
     * when len is less than shape.size(), the rest part will be filled with value_type() */
    explicit Matrix(const Shape &shape, const_pointer data, const size_type &len);

    /* Construct a matrix from an array
     * when N is less than shape.size(), the rest part will be filled with value_type() */
    template <size_type N>
    explicit inline Matrix(const Shape &shape, const value_type (&array)[N])
        : Matrix(shape, N == 0 ? nullptr : &array[0], N) {}

    /* Construct a matrix from an std::array
     * when N is less than shape.size(), the rest part will be filled with value_type() */
    template <size_type N>
    explicit inline Matrix(const Shape &shape, std::array<value_type, N> &array)
        : Matrix(shape, N == 0 ? nullptr : std::data(array), N) {}

    /* Construct a matrix with shape and defaultValue */
    explicit inline Matrix(const Shape &shape, const_reference defaultValue = value_type()) {
        allocateMemory(shape);
        fill(defaultValue);
    }

    /* Construct a diagonal matrix, the diag is the diagonal elements
     * Matrix<int>(Diag({1, 2, 3, 4})) will construct a matrix whose shape is Shape(4, 4),
     * diagonal elements are 1, 2, 3, 4 and other elements are value_type()
     * In this case, int() will be 0 */
    template <class Container>
    explicit Matrix(const _Diag<Container> &diag);

    /* Copy constructor
     * If other's value_type is not same with current matrix's,
     * the other's elements will be cast to the current matrix's value_type with static_cast<> */
    template <class T1>
    inline Matrix(const Matrix<T1> &other) {
        *this = other;
    }
    inline Matrix(const Matrix &other) { *this = other; }

    /* Move constructor
     * NOTE: only those which have the same value_type can use move constructor
     */
    inline Matrix(Matrix &&other) noexcept { *this = std::move(other); }

    /* Move assignment
     * NOTE: only those which have the same value_type can use move assignment */
    inline Matrix &operator=(Matrix &&other) noexcept {
        _shape = std::move(other._shape);
        _data  = std::move(other._data);
        return *this;
    }

    /* Copy assignment
     * If other's value_type is not same with current matrix's,
     * the other's elements will be cast to the current matrix's value_type with static_cast<> */
    template <class T1>
    Matrix<value_type> &operator=(const Matrix<T1> &other);
    inline Matrix<value_type> &operator=(const Matrix &other) {
        return operator=<value_type>(other);
    }

    /* Get the reference to the element of i-th row, j-th column */
    inline reference get(const size_type &i, const size_type &j) {
        assert(i < rows() && j < columns());
        return (*this)[i * columns() + j];
    }
    inline const_reference get(const size_type &i, const size_type &j) const {
        assert(i < rows() && j < columns());
        return (*this)[i * columns() + j];
    }

    /* Get the element at pos
     * The elements are numbered sequentially from left to right and top to bottom. */
    inline reference operator[](const size_type &pos) {
        assert(pos < size());
        return data()[pos];
    }
    inline const_reference operator[](const size_type &pos) const {
        assert(pos < size());
        return data()[pos];
    }

    /* Get the date pointer */
    inline pointer data() noexcept { return _data.get(); }
    inline const_pointer data() const noexcept { return _data.get(); }

    /* Get the number of rows */
    inline size_type rows() const noexcept { return _shape.rows; }

    /* Get the number of columns */
    inline size_type columns() const noexcept { return _shape.columns; }

    /* Get the number of elements */
    inline size_type size() const noexcept { return _shape.size(); }

    /* Get the matrix's shape */
    inline Shape shape() const noexcept { return _shape; }

    /* Reshape the matrix
     * NOTE: this is only valid, when the new shape has the size with the old one */
    inline void reshape(const Shape &shape) noexcept {
        assert(_shape.size() == shape.size());
        _shape = shape;
    }

    /* Make all the elements of the matrix be a new value, when pos = 0
     * Otherwise, the elements before pos will not changed
     * pos should be less than or equal to size() */
    void fill(const_reference value, const size_type &pos = 0);

    /* Calculate number ^ (*this), and store the result in output
     * The function whose parameters do not include output will change (*this)
     * NOTE: (*this) must have the same shape with output
     *       If O and value_type are not same, all the elements will first be cast to
     *       std::common_type_t<O, value_type>, after calculation they will be cast into O
     *       by using static_cast
     * for example: a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              a.numberPow(2, output)
     *              output: [[2^1, 2^2, 2^3],
     *                       [2^2, 2^3, 2^4]]
     *              a.numberPow(2)
     *              a: [[2^1, 2^2, 2^3],
     *                  [2^2, 2^3, 2^4]] */
    template <class Number, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
    void numberPow(const Number &number, Matrix<O> &output) const;
    template <class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
    inline void numberPow(const Number &number) {
        numberPow(number, *this);
    }

    /* Calculate (*this) ^ number, and store the result in output
     * The function whose parameters do not include output will change (*this)
     * NOTE: (*this) must have the same shape with output
     *       If O and value_type are not same, all the elements will first be cast to
     *       std::common_type_t<O, value_type>, after calculation they will be cast into O
     *       by using static_cast
     * for example: a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              a.powNumber(2, output)
     *              output: [[1^2, 2^2, 3^2],
     *                       [2^2, 3^2, 4^2]]
     *              a.numberPow(2)
     *              a: [[1^2, 2^2, 3^2],
     *                  [2^2, 3^2, 4^2]] */
    template <class Number, class O, class = std::enable_if_t<!is_matrix_v<Number>>>
    void powNumber(const Number &number, Matrix<O> &output) const;
    template <class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
    inline void powNumber(const Number &number) {
        powNumber(number, *this);
    }

    /* Calculate (*this) ^ exponent, and store the result in output
     * This is different with powNumber or numberPow
     * This will calculate the matrix exponentiation
     * This is only valid when (*this) is a square matrix
     * The function whose parameters do not include output will change (*this)
     * NOTE: (*this) must be a square matrix
     *       (*this) must have the same shape with output
     *       If O and value_type are not same, all the elements will first be cast to
     *       std::common_type<O, value_type>, after calculation they will be cast into O
     *       by using static_cast
     * for example: a = [[1, 2],
     *                   [2, 3]]
     *              a.pow(2, output)
     *              output = [[5, 8],
     *                        [8, 13]] */
    template <class O>
    void pow(const size_type &exponent, Matrix<O> &output) const;
    inline void pow(const size_type &exponent) { pow(exponent, *this); }

    /* Return the transposed matrix of (*this)
     * for example: a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              a.transpose()
     *              a: [[1, 2, 3],
     *                  [2, 3, 4]]
     *              return: [[1, 2],
     *                       [2, 3],
     *                       [3, 4]] */
    inline Matrix transpose() const {
        Matrix<value_type> output(Shape{columns(), rows()});
        mca::transpose(*this, output);
        return output;
    }

    /* Check if the matrix is a square matrix */
    inline bool isSquare() const noexcept { return rows() == columns(); }

    /* Check if the matrix is symmetric with multi-thread */
    bool symmetric() const noexcept;

    /* Check if the matrix is antisymmetric with multi-thread */
    bool antisymmetric() const noexcept;

    /* Rreturn iterators */
    inline iterator begin() noexcept { return iterator(data()); }
    inline iterator end() noexcept { return iterator(data() + size()); }
    inline const_iterator begin() const noexcept { return cbegin(); }
    inline const_iterator end() const noexcept { return cend(); }
    inline const_iterator cbegin() const noexcept { return const_iterator(data()); }
    inline const_iterator cend() const noexcept { return const_iterator(data() + size()); }

    /* Rreturn reverse iterators */
    inline reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    inline reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    inline const_reverse_iterator rbegin() const noexcept { return crbegin(); }
    inline const_reverse_iterator rend() const noexcept { return crend(); }
    inline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    inline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    /* Return the fist element of the matrix
     * NOTE: The size() must be greater than 0 */
    inline reference front() {
        assert(size() > 0);
        return (*this)[0];
    }
    inline const_reference front() const {
        assert(size() > 0);
        return (*this)[0];
    }

    /* Return the last element of the matrix
     * NOTE: The size() must be greater than 0 */
    inline reference back() {
        assert(size() > 0);
        return (*this)[size() - 1];
    }
    inline const_reference back() const {
        assert(size() > 0);
        return (*this)[size() - 1];
    }

    /* Check if the current matrix is empty */
    inline bool empty() const noexcept { return size() == 0; }

    /* Swap the contents
     * NOTE: only those which have the same value_type can use swap */
    inline void swap(Matrix &other) noexcept {
        std::swap(_shape, other._shape);
        _data.swap(other._data);
    }

private:
    /* Allocate memory for _data, and update _shape with shape */
    inline void allocateMemory(const Shape &shape) {
        // no need to re-allocate
        if (size() == shape.size()) {
            _shape = shape;
            return;
        }
        _shape = shape;
        if (size() == 0) {
            _data = nullptr;
            return;
        }
        _data = std::make_unique<value_type[]>(size());
    }

    std::unique_ptr<value_type[]> _data;
    Shape _shape;
};

template <class T>
Matrix<T>::Matrix(const Shape &shape, const IdentityMatrix &) {
    allocateMemory(shape);
    fill(value_type());
    size_type totalCalculation = std::min(rows(), columns());
    if (threadNum() == 0 || limit() >= totalCalculation) {
        for (size_type i = 0; i < totalCalculation; i++) { get(i, i) = value_type(1); }
        return;
    }
    auto res = threadCalculationTaskNum(totalCalculation);
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first]() {
                for (size_type i = start; i < end; i++) { get(i, i) = value_type(1); }
            });
    }
    for (size_type i = (res.second - 1) * res.first; i < totalCalculation; i++) {
        get(i, i) = value_type(1);
    }
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<value_type>> &init) {
    allocateMemory(Shape(init.size(), init.size() == 0 ? 0 : init.begin()->size()));
    if (threadNum() == 0 || limit() >= size()) {
        for (size_type i = 0; i < rows(); i++)
            for (size_type j = 0; j < columns(); j++) {
                get(i, j) = std::data(std::data(init)[i])[j];
            }
        return;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first, &init]() {
                for (size_type i = start; i < end; i++) {
                    (*this)[i] = static_cast<value_type>(
                        std::data(std::data(init)[i / columns()])[i % columns()]);
                }
            });
    }

    for (size_type i = (res.second - 1) * res.first; i < size(); i++) {
        (*this)[i] =
            static_cast<value_type>(std::data(std::data(init)[i / columns()])[i % columns()]);
    }
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<value_type>> &init) {
    allocateMemory(Shape(init.size(), init.size() == 0 ? 0 : init.begin()->size()));
    if (threadNum() == 0 || limit() >= size()) {
        for (size_type i = 0; i < rows(); i++)
            for (size_type j = 0; j < columns(); j++) { get(i, j) = init[i][j]; }
        return;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first, &init]() {
                for (size_type i = start; i < end; i++) {
                    (*this)[i] = static_cast<value_type>(init[i / columns()][i % columns()]);
                }
            });
    }
    for (size_type i = (res.second - 1) * res.first; i < size(); i++) {
        (*this)[i] = static_cast<value_type>(init[i / columns()][i % columns()]);
    }
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
Matrix<T>::Matrix(const Shape &shape, const_pointer data, const size_type &len) {
    allocateMemory(shape);

    // the actual length of elements in data will be used
    size_type actualLen = std::min(size(), len);
    if (threadNum() == 0 || limit() >= actualLen) {
        for (size_type i = 0; i < actualLen; i++) { (*this)[i] = static_cast<value_type>(data[i]); }
        if (size() > actualLen) { fill(value_type(), actualLen); }
        return;
    }

    auto res = threadCalculationTaskNum(actualLen);
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, start = i * res.first, end = (i + 1) * res.first, data]() {
                for (size_type i = start; i < end; i++) {
                    (*this)[i] = static_cast<value_type>(data[i]);
                }
            });
    }
    for (size_type i = (res.second - 1) * res.first; i < actualLen; i++) {
        (*this)[i] = static_cast<value_type>(data[i]);
    }
    for (auto &item : returnValue) { item.get(); }
    if (size() > actualLen) { fill(value_type(), actualLen); }
}

template <class T>
template <class Container>
Matrix<T>::Matrix(const _Diag<Container> &diag) {
    allocateMemory(Shape(diag.size(), diag.size()));
    fill(value_type());
    if (threadNum() == 0 || limit() >= rows()) {
        for (size_type i = 0; i < rows(); i++) { get(i, i) = diag[i]; }
        return;
    }
    auto res = threadCalculationTaskNum(rows());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] =
            threadPool().addTask([this, &diag, start = i * res.first, end = (i + 1) * res.first]() {
                for (size_type i = start; i < end; i++) { get(i, i) = diag[i]; }
            });
    }
    for (size_type i = (res.second - 1) * res.first; i < rows(); i++) { get(i, i) = diag[i]; }
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
template <class T1>
Matrix<T> &Matrix<T>::operator=(const Matrix<T1> &other) {
    allocateMemory(other.shape());
    if (threadNum() == 0 || limit() >= size()) {
        for (size_type i = 0; i < size(); i++) { (*this)[i] = static_cast<value_type>(other[i]); }
        return *this;
    }
    auto res = threadCalculationTaskNum(size());
    std::vector<std::future<void>> returnValue(res.second - 1);
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first, end = (i + 1) * res.first, &other]() {
                for (size_type i = start; i < end; i++) {
                    (*this)[i] = static_cast<value_type>(other[i]);
                }
            });
    }
    for (size_type i = (res.second - 1) * res.first; i < size(); i++) {
        (*this)[i] = static_cast<value_type>(other[i]);
    }
    for (auto &item : returnValue) { item.get(); }
    return *this;
}

template <class T>
void Matrix<T>::fill(const_reference value, const size_type &pos) {
    if (size() <= pos) { return; }
    // single mode
    if (threadNum() == 0 || limit() >= size() - pos) {
        std::fill(data() + pos, data() + size(), value);
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(size() - pos);

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);
    // assign task for every sub-thread
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first + pos, end = (i + 1) * res.first + pos, &value]() {
                std::fill(data() + start, data() + end, value);
            });
    }
    // let main thread calculate too
    std::fill(data() + (res.second - 1) * res.first + pos, data() + size(), value);

    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
template <class Number, class O, class>
void Matrix<T>::numberPow(const Number &number, Matrix<O> &output) const {
    // single mode
    if (threadNum() == 0 || limit() >= size()) {
        numberPowSingleThread(number, *this, output, 0, size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(size());

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);
    // assign task for every sub-thread
    for (size_type i = 0; i < res.second - 1; i++) {
        returnValue[i] = threadPool().addTask(
            [this, start = i * res.first, len = res.first, &output, &number]() {
                numberPowSingleThread(number, *this, output, start, len);
            });
    }
    // let main thread calculate took
    numberPowSingleThread(number,
                          *this,
                          output,
                          (res.second - 1) * res.first,
                          (size() - (res.second - 1) * res.first));

    // make sure all the sub threads are finished
    for (auto &item : returnValue) { item.get(); }
}

template <class T>
template <class Number, class O, class>
void Matrix<T>::powNumber(const Number &number, Matrix<O> &output) const {
    // single mode
    if (threadNum() == 0 || limit() >= size()) {
        powNumberSingleThread(*this, number, output, 0, size());
        return;
    }
    // threadCalculation and taskNum
    auto res = threadCalculationTaskNum(size());

    // the return value of every task, use this to make sure every task is finished
    std::vector<std::future<void>> returnValue(res.second - 1);
    // assign task for every sub-thread
    for (size_type i = 0; i < res.second - 1; i++) {
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

template <class T>
template <class O>
void Matrix<T>::pow(const size_type &exponent, Matrix<O> &output) const {
    assert(isSquare());
    assert(shape() == output.shape());
    size_type b = exponent;
    Matrix<value_type> a(*this);
    // make output an identity matrix
    output = Matrix<O>(output.shape(), IdentityMatrix());
    while (b > 0) {
        if (b & 1) { output *= a; }
        if ((b >> 1) == 0) { break; }
        a *= a;
        b >>= 1;
    }
}

// TODO
template <class T>
bool Matrix<T>::symmetric() const noexcept {}
template <class T>
bool Matrix<T>::antisymmetric() const noexcept {}
}  // namespace mca

#endif
