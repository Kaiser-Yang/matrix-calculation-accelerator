#include <gtest/gtest.h>

#include <cmath>

#include "mca/__mca_internal/single_thread_matrix_calculation.h"
#include "mca/matrix.h"

namespace mca {
namespace test {
class TestSameAddress : public testing::Test {
protected:
    Matrix<double> a, b;
    void SetUp() override { a = b = Matrix<double>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}); }

    void TearDown() override {}
};

TEST_F(TestSameAddress, powNumber) {
    powNumberSingleThread(a, 2, a, 0, a.size());
    Matrix<double> result{{1, 2 * 2, 3 * 3}, {4 * 4, 5 * 5, 6 * 6}, {7 * 7, 8 * 8, 9 * 9}};
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, numberPow) {
    numberPowSingleThread(2, a, a, 0, a.size());
    Matrix<double> result({{std::pow(2, 1), std::pow(2, 2), std::pow(2, 3)},
                           {std::pow(2, 4), std::pow(2, 5), std::pow(2, 6)},
                           {std::pow(2, 7), std::pow(2, 8), std::pow(2, 9)}});
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, addNumber) {
    addSingleThread(2, a, a, 0, a.size());
    Matrix<double> result({{2 + 1, 2 + 2, 2 + 3}, {2 + 4, 2 + 5, 2 + 6}, {2 + 7, 2 + 8, 2 + 9}});
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, subtractNumber) {
    subtractSingleThread(a, 2, a, 0, a.size());
    Matrix<double> result1({{1 - 2, 2 - 2, 3 - 2}, {4 - 2, 5 - 2, 6 - 2}, {7 - 2, 8 - 2, 9 - 2}});
    subtractSingleThread(2, b, b, 0, b.size());
    Matrix<double> result2({{2 - 1, 2 - 2, 2 - 3}, {2 - 4, 2 - 5, 2 - 6}, {2 - 7, 2 - 8, 2 - 9}});
    ASSERT_TRUE(equalSingleThread(a, result1, 0, a.size()));
    ASSERT_TRUE(equalSingleThread(b, result2, 0, b.size()));
}

TEST_F(TestSameAddress, multiplyNumber) {
    multiplySingleThread(2, a, a, 0, a.size());
    Matrix<double> result({{2 * 1, 2 * 2, 2 * 3}, {2 * 4, 2 * 5, 2 * 6}, {2 * 7, 2 * 8, 2 * 9}});
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, divideNumber) {
    divideSingleThread(a, 2, a, 0, a.size());
    // clang-format off
    Matrix<double> result1({{1. / 2, 2. / 2, 3. / 2},
                      {4. / 2, 5. / 2, 6. / 2},
                      {7. / 2, 8. / 2, 9. / 2}});
    // clang-format on
    divideSingleThread(2, b, b, 0, b.size());
    // clang-format off
    Matrix<double> result2({{2. / 1, 2. / 2, 2. / 3},
                      {2. / 4, 2. / 5, 2. / 6},
                      {2. / 7, 2. / 8, 2. / 9}});
    // clang-format on
    ASSERT_TRUE(equalSingleThread(a, result1, 0, a.size()));
    ASSERT_TRUE(equalSingleThread(b, result2, 0, b.size()));
}

TEST_F(TestSameAddress, addMatrix) {
    addSingleThread(a, a, a, 0, a.size());
    Matrix<double> result({{1 + 1, 2 + 2, 3 + 3}, {4 + 4, 5 + 5, 6 + 6}, {7 + 7, 8 + 8, 9 + 9}});
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, subtractMatrix) {
    subtractSingleThread(a, a, a, 0, a.size());
    Matrix<double> result({{1 - 1, 2 - 2, 3 - 3}, {4 - 4, 5 - 5, 6 - 6}, {7 - 7, 8 - 8, 9 - 9}});
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}
}  // namespace test
}  // namespace mca
