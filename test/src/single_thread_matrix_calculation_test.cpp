#include "single_thread_matrix_calculation.h"

#include <gtest/gtest.h>

#include <cmath>

#include "matrix.h"

namespace mca {
namespace test {
class TestSinglThreadCalculation : public testing::Test {
protected:
    Matrix<> one, negOne, output, a, b, c, d;

    void SetUp() override {
        one    = Matrix<>({3, 3}, 1);
        negOne = Matrix<>({3, 3}, -1);
        a      = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        b      = Matrix<>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
        c      = Matrix<>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        d      = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
    }

    void TearDown() override {}
};

TEST_F(TestSinglThreadCalculation, powWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    powSingleThread(2, a, output, 0, 0, a.getShape());
    for (size_t i = 0; i < output.rows(); i++) {
        for (size_t j = 0; j < output.columns(); j++) {
            ASSERT_DOUBLE_EQ(std::pow(2.0, i), output.get(i, j));
        }
    }
    powSingleThread(a, 2, output, 0, 0, a.getShape());
    for (size_t i = 0; i < output.rows(); i++) {
        for (size_t j = 0; j < output.columns(); j++) {
            ASSERT_DOUBLE_EQ(std::pow(i, 2.0), output.get(i, j));
        }
    }
}

TEST_F(TestSinglThreadCalculation, powSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    powSingleThread(2, c, output, 0, 1, {2, 2});
    Matrix<> result({{-1, 4, 8}, {-1, 32, 64}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
    output = Matrix<>({3, 3}, -1);
    powSingleThread(c, 2, output, 0, 1, {2, 2});
    result = Matrix({{-1, 4, 9}, {-1, 25, 36}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessWholeMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 0, 0, a.getShape()));
    ASSERT_FALSE(lessSingleThread(a, b, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessSubMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 1, 0, {2, 3}));
    ASSERT_FALSE(lessSingleThread(a, b, 1, 0, {2, 2}));
}

TEST_F(TestSinglThreadCalculation, equalWholeMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 0, 0, a.getShape()));
    ASSERT_FALSE(equalSingleThread(a, b, 0, 0, a.getShape()));
}
TEST_F(TestSinglThreadCalculation, equalSubMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 1, 0, {2, 2}));
    ASSERT_FALSE(equalSingleThread(a, b, 1, 0, {2, 2}));
}

TEST_F(TestSinglThreadCalculation, lessEqualWholeMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 0, 0, a.getShape()));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 0, 0, a.getShape()));
    ASSERT_FALSE(lessEqualSingleThread(c, b, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessEqualSubMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 0, 0, {2, 3}));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 0, 0, {2, 3}));
    ASSERT_FALSE(lessEqualSingleThread(c, a, 0, 0, {2, 3}));
}

// TODO
TEST_F(TestSinglThreadCalculation, greaterWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, greaterSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, greaterEqualWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, greaterEqualSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, notEqualWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, notEqualSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, addNumberWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, addNumberSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, sustractNumberWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, sustractNumberSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, multiplyNumberWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, multiplyNumberSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, divideNumberWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, divideNumberSubMatrix) {}

TEST_F(TestSinglThreadCalculation, addWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    addSingleThread(a, b, output, 0, 0, a.getShape());
    Matrix<> result({{1, 0, 0}, {1, 2, 1}, {2, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    addSingleThread(b, a, output, 0, 0, b.getShape());
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, addSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(a, b, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 2, 1}, {-1, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    addSingleThread(b, a, output, 1, 1, {2, 2});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, sustractWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    substractSingleThread(a, b, output, 0, 0, a.getShape());
    Matrix<> result({{-1, 0, 0}, {1, 0, 1}, {2, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    substractSingleThread(b, a, output, 0, 0, b.getShape());
    result = Matrix<>({{1, 0, 0}, {-1, 0, -1}, {-2, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, sustractSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    substractSingleThread(a, b, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 0, 1}, {-1, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    substractSingleThread(b, a, output, 1, 1, {2, 2});
    result = Matrix<>({{-1, -1, -1}, {-1, 0, -1}, {-1, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, multiplyWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    multiplySingleThread(a, one, output, 0, 0, a.getShape());
    Matrix<> result({{0, 0, 0}, {3, 3, 3}, {6, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    multiplySingleThread(one, a, output, 0, 0, one.getShape());
    result = Matrix<>({3, 3}, 3);
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, multiplySubMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(a, one, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 3, 3}, {-1, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    multiplySingleThread(one, a, output, 1, 1, {2, 2});
    result = Matrix<>({{-1, -1, -1}, {-1, 3, 3}, {-1, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, transposeWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    transposeSingleThread(c, output, 0, 0, c.getShape());
    Matrix<> result({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, transposeSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    transposeSingleThread(c, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 5, 8}, {-1, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}
}  // namespace test
}  // namespace mca
