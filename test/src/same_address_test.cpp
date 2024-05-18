#include <gtest/gtest.h>

#include "matrix.h"
#include "single_thread_matrix_calculation.h"

namespace mca {
namespace test {
class TestSameAddress : public testing::Test {
protected:
    Matrix<> a;
    void SetUp() override { a = Matrix<>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}); }

    void TearDown() override {}
};

TEST_F(TestSameAddress, powNumber) {
    powNumberSingleThread(a, 2, a, 0, a.size());
    Matrix<> result = {{1, 2 * 2, 3 * 3}, {4 * 4, 5 * 5, 6 * 6}, {7 * 7, 8 * 8, 9 * 9}};
    ASSERT_TRUE(equalSingleThread(a, result, 0, a.size()));
}

TEST_F(TestSameAddress, numberPow) {}

TEST_F(TestSameAddress, addNumber) {}

TEST_F(TestSameAddress, subtractNumber) {}

TEST_F(TestSameAddress, multiplyNumber) {}

TEST_F(TestSameAddress, divideNumber) {}

TEST_F(TestSameAddress, addMatrix) {}

TEST_F(TestSameAddress, sustractMatrix) {}
}  // namespace test
}  // namespace mca
