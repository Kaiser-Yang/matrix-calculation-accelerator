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
#include "mca/__mca_internal/utility.h"
#include "mca/mca_config.h"
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
    explicit inline Matrix(const Shape &shape, const _IdentityMatrix &) {
        allocateMemory(shape);
        fill(value_type());
        size_type totalCalculation = std::min(rows(), columns());
        calculationHelper(Operation::MATRIX_CONSTRUCT_IDENTITY,
                          totalCalculation,
                          threadCalculationTaskNum(totalCalculation),
                          nullptr,
                          [this](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  get(i, i) = value_type(1);
                              }
                          });
    }

    /* Construct a matrix from a initializer_list
     * You can use this like Matrix<int>({{1, 2}, {3, 4}}) */
    explicit inline Matrix(const std::initializer_list<std::initializer_list<value_type>> &init) {
        allocateMemory(Shape(init.size(), init.size() == 0 ? 0 : init.begin()->size()));
        calculationHelper(Operation::MATRIX_CONSTRUCT_FROM_INITIALIZER_LIST,
                          size(),
                          threadCalculationTaskNum(size()),
                          nullptr,
                          [this, &init](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  (*this)[i] = static_cast<value_type>(
                                      std::data(std::data(init)[i / columns()])[i % columns()]);
                              }
                          });
    }

    /* Construct a matrix from a vector */
    explicit inline Matrix(const std::vector<std::vector<value_type>> &init) {
        allocateMemory(Shape(init.size(), init.size() == 0 ? 0 : init.begin()->size()));
        calculationHelper(Operation::MATRIX_CONSTRUCT_FROM_VECTOR,
                          size(),
                          threadCalculationTaskNum(size()),
                          nullptr,
                          [this, &init](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  (*this)[i] =
                                      static_cast<value_type>(init[i / columns()][i % columns()]);
                              }
                          });
    }

    /* Construct a matrix from a pointer
     * when len is less than shape.size(), the rest part will be filled with value_type() */
    explicit inline Matrix(const Shape &shape, const_pointer data, const size_type &len) {
        allocateMemory(shape);
        // the actual length of elements in data will be used
        size_type actualLen = std::min(size(), len);
        calculationHelper(Operation::MATRIX_CONSTRUCT_FROM_POINTER,
                          actualLen,
                          threadCalculationTaskNum(actualLen),
                          nullptr,
                          [this, &data, &actualLen](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  (*this)[i] = static_cast<value_type>(data[i]);
                              }
                          });
        if (size() > actualLen) { fill(value_type(), actualLen); }
    }

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
    explicit inline Matrix(const _Diag<Container> &diag) {
        allocateMemory(Shape(diag.size(), diag.size()));
        fill(value_type());
        calculationHelper(Operation::MATRIX_CONSTRUCT_DIAG,
                          rows(),
                          threadCalculationTaskNum(rows()),
                          nullptr,
                          [this, &diag](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  get(i, i) = diag[i];
                              }
                          });
    }

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
    inline Matrix &operator=(const Matrix<T1> &other) {
        allocateMemory(other.shape());
        calculationHelper(Operation::MATRIX_COPY_ASSIGNMENT,
                          size(),
                          threadCalculationTaskNum(size()),
                          nullptr,
                          [this, &other](const size_type &start, const size_type &len) {
                              for (size_type i = start; i < start + len; i++) {
                                  (*this)[i] = static_cast<value_type>(other[i]);
                              }
                          });
        return *this;
    }
    inline Matrix &operator=(const Matrix &other) { return operator=<value_type>(other); }

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
    inline void fill(const_reference value, const size_type &pos = 0) {
        calculationHelper(Operation::MATRIX_FILL,
                          size() - pos,
                          threadCalculationTaskNum(size() - pos),
                          nullptr,
                          [this, &value, &pos](const size_type &start, const size_type &len) {
                              std::fill(data() + pos + start, data() + pos + start + len, value);
                          });
    }

    /* Calculate number ^ (*this), and return the result
     * This function do not change the (*this)
     * for example: a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              a.numberPow(2)
     *              a: [[1, 2, 3],
     *                  [2, 3, 4]]
     *              return: [[2^1, 2^2, 2^3],
     *                       [2^2, 2^3, 2^4]] */
    template <class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
    inline Matrix numberPow(const Number &number) {
        Matrix<value_type> output(shape());
        mca::numberPow(number, *this, output);
        return output;
    }

    /* Calculate (*this) ^ number, and return the result
     * This function do not change the (*this)
     * for example: a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              a.powNumber(2)
     *              a = [[1, 2, 3],
     *                   [2, 3, 4]]
     *              return: [[1^2, 2^2, 3^2],
     *                       [2^2, 3^2, 4^2]] */
    template <class Number, class = std::enable_if_t<!is_matrix_v<Number>>>
    inline Matrix powNumber(const Number &number) {
        Matrix<value_type> output(shape());
        mca::powNumber(*this, number, output);
        return output;
    }

    /* Calculate (*this) ^ exponent, and return the result
     * This function do not change the (*this)
     * This is different with powNumber or numberPow
     * This will calculate the matrix exponentiation
     * This is only valid when (*this) is a square matrix
     * for example: a = [[1, 2],
     *                   [2, 3]]
     *              a.pow(2)
     *              return:  [[5, 8],
     *                        [8, 13]] */
    inline Matrix pow(const size_type &exponent) const {
        assert(square());
        Matrix<value_type> output(shape());
        mca::pow(*this, exponent, output);
        return output;
    }

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
    inline bool square() const noexcept { return rows() == columns(); }

    /* Check if the matrix is symmetric with multi-thread */
    inline bool symmetric() const {
        if (!square()) { return false; }
        bool result = false;
        calculationHelper(Operation::MATRIX_SYMMETRIC,
                          size(),
                          threadCalculationTaskNum(size()),
                          result,
                          [this](const size_type &start, const size_type &len) {
                              return symmetricSingleThread(*this, start, len);
                          });
        return result;
    }

    /* Check if the matrix is antisymmetric with multi-thread */
    inline bool antisymmetric() const {
        if (!square()) { return false; }
        bool result = false;
        calculationHelper(Operation::MATRIX_ANTISYMMETRIC,
                          size(),
                          threadCalculationTaskNum(size()),
                          result,
                          [this](const size_type &start, const size_type &len) {
                              return antisymmetricSingleThread(*this, start, len);
                          });
        return result;
    }

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
}  // namespace mca

#endif
