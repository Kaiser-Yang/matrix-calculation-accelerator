#include "matrix.h"

#include <gtest/gtest.h>

#include <vector>

#include "single_thread_matrix_calculation.h"

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
    ASSERT_EQ(m.getShape(), Shape(0, 0));
    ASSERT_EQ(m.dataPtr(), nullptr);

    // construct a matrix with a specified value
    Matrix<int> m1(Shape{3, 3}, -1);
    ASSERT_EQ(m1.getShape(), Shape(3, 3));
    ASSERT_NE(m1.dataPtr(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), -1); }
    }

    // construct from a std::initializer_list
    Matrix<int> m2({{-1, -1, -1}, {-1, -1, -1}});
    ASSERT_EQ(m2.getShape(), Shape(2, 3));
    ASSERT_NE(m2.dataPtr(), nullptr);
    for (size_t i = 0; i < m2.rows(); i++) {
        for (size_t j = 0; j < m2.columns(); j++) { ASSERT_EQ(m2.get(i, j), -1); }
    }

    // construct an identity matrix
    Matrix<int> m3(Shape{3, 3});
    Matrix<int> result({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    ASSERT_TRUE(equalSingleThread(m3, result, 0, 0, m3.getShape()));

    // construct from a pointer
    int data[] = {1, 2, 3};
    Matrix<int> m4({3, 3}, &data[0], 3);
    result = Matrix<int>({{1, 2, 3}, {0, 0, 0}, {0, 0, 0}});
    ASSERT_TRUE(equalSingleThread(m4, result, 0, 0, m4.getShape()));

    // construct from a vector
    std::vector<std::vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m5(vec);
    result = Matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    ASSERT_TRUE(equalSingleThread(m5, result, 0, 0, m5.getShape()));

    // construct a diagonal matrix
    Matrix<int> m6({1, 2, 3});
    result = Matrix<int>({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});
    ASSERT_TRUE(equalSingleThread(m6, result, 0, 0, m6.getShape()));
    Matrix<int> m7(std::vector<int>{1, 2, 3});
    result = Matrix<int>({{1, 0, 0}, {0, 2, 0}, {0, 0, 3}});
    ASSERT_TRUE(equalSingleThread(m6, result, 0, 0, m6.getShape()));
}

TEST(TestMatrix, assignments) {
    Matrix<int> m;
    ASSERT_EQ(m.getShape(), Shape(0, 0));
    ASSERT_EQ(m.dataPtr(), nullptr);

    // move assignment from Matrix<int>
    m = Matrix<int>({3, 3}, 1);
    ASSERT_EQ(m.getShape(), Shape(3, 3));
    ASSERT_NE(m.dataPtr(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), 1); }
    }

    // move assignment from Matrix<double>
    m = Matrix<>({3, 3}, 1.5);
    Matrix<int> result({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(m, result, 0, 0, m.getShape()));

    // copy assignment from Matrix<int>
    Matrix<int> newN({3, 3}, 1);
    m = newN;
    ASSERT_EQ(m.getShape(), Shape(3, 3));
    ASSERT_NE(m.dataPtr(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), 1); }
    }

    // copy assignment from Matrix<double>
    Matrix<double> newM = Matrix<>({3, 3}, 1.5);
    result              = newM;
    ASSERT_TRUE(equalSingleThread(m, result, 0, 0, m.getShape()));

    // copy assignment from a pointer
    double data[9] = {1.5, 2.5, 3.5};
    m              = &data[0];
    result         = Matrix<>({3, 3}, &data[0], 3);
    ASSERT_TRUE(equalSingleThread(m, result, 0, 0, m.getShape()));

    // copy assignment from std::initializer_list
    m      = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    result = Matrix<>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    ASSERT_TRUE(equalSingleThread(m, result, 0, 0, m.getShape()));

    // copy assignment from a std::vector
    std::vector<std::vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m = Matrix<>();
    m = vec;
    ASSERT_TRUE(equalSingleThread(m, result, 0, 0, m.getShape()));
}

TEST(TestMatrix, geter) {
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    ASSERT_EQ(m.getShape(), Shape(3, 3));
    for (size_t i = 0; i < m.getShape().rows; i++) {
        for (size_t j = 0; j < m.getShape().columns; j++) {
            ASSERT_EQ(m.get(i, j), i * 3 + j + 1);
            m.get(i, j) = 0;
            ASSERT_EQ(m.get(i, j), 0);
        }
    }
}

TEST(TestMatrix, reshape) {
    Matrix<int> m({{1, 2, 3, 4, 5, 6}});
    ASSERT_EQ(m.getShape(), Shape(1, 6));
    m.reshape({2, 3});
    ASSERT_EQ(m.getShape(), Shape(2, 3));
}
}  // namespace test
}  // namespace mca
