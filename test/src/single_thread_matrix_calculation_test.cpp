#include "single_thread_matrix_calculation.h"

#include <gtest/gtest.h>

#include <cmath>

#include "matrix.h"

namespace mca {
namespace test {
class TestSinglThreadCalculation : public testing::Test {
protected:
    Matrix<> one, negOne, output, a, b;

    void SetUp() override {
        one    = Matrix<>({3, 3}, 1);
        negOne = Matrix<>({3, 3}, -1);
        a      = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        b      = Matrix<>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
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
// TODO
TEST_F(TestSinglThreadCalculation, powSubMatrix) {}

// TODO
TEST_F(TestSinglThreadCalculation, lessWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, lessSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, equalWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, equalSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, lessEqualWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, lessEqualSubMatrix) {}
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
// TODO
TEST_F(TestSinglThreadCalculation, addWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, addSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, sustractWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, sustractSubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, multiplyWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, multiplySubMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, transposeWholeMatrix) {}
// TODO
TEST_F(TestSinglThreadCalculation, transposeSubMatrix) {}
}  // namespace test
}  // namespace mca
