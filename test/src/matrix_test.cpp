#include "mca/matrix.h"

#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "mca/__mca_internal/single_thread_matrix_calculation.h"
#include "mca/diag.h"
#include "mca/mca.h"

namespace mca {
namespace test {
TEST(TestShape, defaultConstructor) {
    Shape s;
    ASSERT_EQ(s.rows, 0);
    ASSERT_EQ(s.columns, 0);
}

TEST(TestShape, equal) {
    Shape s1{4, 5};
    Shape s2{4, 5};
    ASSERT_EQ(s1, s2);
}

TEST(TestShape, notEqual) {
    Shape s1{4, 5};
    Shape s2{4, 4};
    ASSERT_NE(s1, s2);
}

TEST(TestShape, size) {
    Shape s{3, 2};
    ASSERT_EQ(s.size(), 3 * 2);
}

// test all constructors in single thread mode
TEST(TestMatrix, constructors) {
    // default constructor
    Matrix<int> m;
    ASSERT_EQ(m.shape(), Shape(0, 0));
    ASSERT_EQ(m.data(), nullptr);

    // construct a matrix with a specified value
    Matrix<int> m1(Shape{3, 3}, -1);
    ASSERT_EQ(m1.shape(), Shape(3, 3));
    ASSERT_NE(m1.data(), nullptr);
    for (size_t i = 0; i < m1.rows(); i++) {
        for (size_t j = 0; j < m1.columns(); j++) { ASSERT_EQ(m1.get(i, j), -1); }
    }

    // construct from a std::initializer_list
    Matrix<int> m2({{-1, -1, -1}, {-1, -1, -1}});
    ASSERT_EQ(m2.shape(), Shape(2, 3));
    ASSERT_NE(m2.data(), nullptr);
    for (size_t i = 0; i < m2.rows(); i++) {
        for (size_t j = 0; j < m2.columns(); j++) { ASSERT_EQ(m2.get(i, j), -1); }
    }

    // construct an identity matrix
    Matrix<int> m3(Shape{3, 3}, IdentityMatrix());
    Matrix<int> result({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    ASSERT_EQ(m3, result);

    // construct from a pointer
    int data[] = {1, 2, 3};
    Matrix<int> m4(Shape{3, 3}, &data[0], 3);
    result = Matrix<int>({{1, 2, 3}, {0, 0, 0}, {0, 0, 0}});
    ASSERT_EQ(m4, result);

    // construct from a vector
    std::vector<std::vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m5(vec);
    result = Matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    ASSERT_EQ(m5, result);

    // construct a diagonal matrix
    Matrix<int> m6(Diag({1, 2, 3}));
    result = Matrix<int>({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});
    ASSERT_EQ(m6, result);
    Matrix<int> m7(Diag(std::vector<int>{1, 2, 3}));
    result = Matrix<int>({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});
    ASSERT_EQ(m7, result);

    // copy constructor
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization): allow tests to copy
    Matrix<int> m8(m7);
    ASSERT_EQ(m7, m8);
    Matrix<double> m9(m8);
    ASSERT_EQ(m8, m9);

    // construct from an array
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> m10(Shape(3, 3), array);
    for (size_t i = 0; i < sizeof(array) / sizeof(int); i++) { ASSERT_EQ(i + 1, m10[i]); }

    // construct from a std::array
    std::array<int, 9> stdArray{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix<int> m11(Shape(3, 3), stdArray);
    for (size_t i = 0; i < stdArray.size(); i++) { ASSERT_EQ(i + 1, m11[i]); }
}

TEST(TestMatrix, assignments) {
    Matrix<int> m;
    ASSERT_EQ(m.shape(), Shape(0, 0));
    ASSERT_EQ(m.data(), nullptr);

    // move assignment from Matrix<int>
    m = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_EQ(m.shape(), Shape(3, 3));
    ASSERT_NE(m.data(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), 1); }
    }

    // copy assignment from Matrix<double>
    m = Matrix<double>(Shape{3, 3}, 1.5);
    Matrix<int> result(Shape{3, 3}, 1);
    ASSERT_EQ(m, result);

    // copy assignment from Matrix<int>
    Matrix<int> newN(Shape{3, 3}, 1);
    m = newN;
    ASSERT_EQ(m.shape(), Shape(3, 3));
    ASSERT_NE(m.data(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), 1); }
    }

    // copy assignment from Matrix<double>
    Matrix<double> newM = Matrix<double>(Shape{3, 3}, 1.5);
    result              = newM;
    ASSERT_EQ(m, result);
}

TEST(TestMatrix, geter) {
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    ASSERT_EQ(m.shape(), Shape(3, 3));
    for (size_t i = 0; i < m.shape().rows; i++) {
        for (size_t j = 0; j < m.shape().columns; j++) {
            ASSERT_EQ(m.get(i, j), i * 3 + j + 1);
            m.get(i, j) = 0;
            ASSERT_EQ(m.get(i, j), 0);
        }
    }
}

TEST(TestMatrix, reshape) {
    Matrix<int> m({{1, 2, 3, 4, 5, 6}});
    ASSERT_EQ(m.shape(), Shape(1, 6));
    m.reshape(Shape{2, 3});
    ASSERT_EQ(m.shape(), Shape(2, 3));
}

TEST(TestMatrix, isSquare) {
    Matrix<int> m(Shape{3, 3});
    ASSERT_TRUE(m.isSquare());
    m.reshape(Shape{1, 9});
    ASSERT_FALSE(m.isSquare());
}

TEST(TestMatrix, iterators) {
    Matrix<double> a(Diag({1, 2, 3, 4}));
    size_t i = 0;
    for (auto &item : a) { ASSERT_FLOAT_EQ(item, a[i++]); }
    for (auto iter = a.rbegin(); iter != a.rend(); iter++) { ASSERT_FLOAT_EQ(*iter, a[--i]); }
    const Matrix<double> b(a);
    for (auto &item : b) { ASSERT_FLOAT_EQ(item, b[i++]); }
    for (auto iter = b.rbegin(); iter != b.rend(); iter++) { ASSERT_FLOAT_EQ(*iter, b[--i]); }
}

TEST(TestMatrix, front) {
    Matrix<double> a({{1, 2, 3}, {4, 5, 6}});
    ASSERT_FLOAT_EQ(a.front(), 1);
    a.front() = -1;
    ASSERT_FLOAT_EQ(a.front(), -1);
}

TEST(TestMatrix, back) {
    Matrix<double> a({{1, 2, 3}, {4, 5, 6}});
    ASSERT_FLOAT_EQ(a.back(), 6);
    a.back() = -1;
    ASSERT_FLOAT_EQ(a.back(), -1);
}

TEST(TestMatrix, empty) {
    Matrix<double> a;
    ASSERT_TRUE(a.empty());
    a = Matrix<double>({{1}});
    ASSERT_FALSE(a.empty());
}

TEST(TestMatrix, swap) {
    Shape shape1{2, 2}, shape2{3, 3};
    double value1 = 1, value2 = -1;
    Matrix<double> a(shape1, value1), b(shape2, value2);
    a.swap(b);
    ASSERT_EQ(a, Matrix<double>(shape2, value2));
    ASSERT_EQ(b, Matrix<double>(shape1, value1));
}
}  // namespace test
}  // namespace mca
