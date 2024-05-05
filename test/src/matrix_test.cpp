#include "matrix.h"

#include <gtest/gtest.h>

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

// test all constructors
TEST(TestMatrix, constructors) {
    Matrix<int> m;
    ASSERT_EQ(m.getShape(), Shape(0, 0));
    ASSERT_EQ(m.dataPtr(), nullptr);
    Matrix<int> m1(Shape{3, 3}, -1);
    ASSERT_EQ(m1.getShape(), Shape(3, 3));
    ASSERT_NE(m1.dataPtr(), nullptr);
    for (size_t i = 0; i < m.getShape().rows; i++) {
        for (size_t j = 0; j < m.getShape().columns; j++) { ASSERT_EQ(m.get(i, j), -1); }
    }
    Matrix<int> m2 = Matrix<int>({{-1, -1, -1}, {-1, -1, -1}});
    ASSERT_EQ(m2.getShape(), Shape(2, 3));
    ASSERT_NE(m2.dataPtr(), nullptr);
    for (size_t i = 0; i < m2.getShape().rows; i++) {
        for (size_t j = 0; j < m2.getShape().columns; j++) { ASSERT_EQ(m2.get(i, j), -1); }
    }
}

TEST(TestMatrix, assignments) {
    Matrix<int> m;
    ASSERT_EQ(m.getShape(), Shape(0, 0));
    ASSERT_EQ(m.dataPtr(), nullptr);
    m = Matrix<int>({3, 3}, 1);
    ASSERT_EQ(m.getShape(), Shape(3, 3));
    ASSERT_NE(m.dataPtr(), nullptr);
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) { ASSERT_EQ(m.get(i, j), 1); }
    }
}

// test get() and getShape()
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
