#include <gtest/gtest.h>

#include "matrix.h"
#include "single_thread_matrix_calculation.h"

namespace mca {
namespace test {
class TestDifferentType : public testing::Test {
protected:
    Matrix<> doubleMatrix, doubleOutput, doubleResult;
    Matrix<int> intMatrix, intOutput, intResult;

    void SetUp() override {
        doubleMatrix = Matrix<>(Shape{3, 3}, -1.);
        doubleOutput = Matrix<>(Shape{3, 3}, 0.);
        intMatrix    = Matrix<int>(Shape{3, 3}, -1);
        intOutput    = Matrix<int>(Shape{3, 3}, 0);
    }

    void TearDown() override {}
};

TEST_F(TestDifferentType, differentTypeComparison) {
    ASSERT_TRUE(equalSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
    ASSERT_FALSE(notEqualSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
    ASSERT_FALSE(lessSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
    ASSERT_TRUE(lessEqualSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
    ASSERT_FALSE(greaterSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
    ASSERT_TRUE(greaterEqualSingleThread(doubleMatrix, intMatrix, 0, doubleMatrix.size()));
}

TEST_F(TestDifferentType, differentTypeCalculation) {
    addSingleThread(intMatrix, doubleMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    addSingleThread(intMatrix, doubleMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    subtractSingleThread(intMatrix, doubleMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    subtractSingleThread(intMatrix, doubleMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    multiplySingleThread(intMatrix, doubleMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 3.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    multiplySingleThread(intMatrix, doubleMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    powNumberSingleThread(doubleMatrix, 2, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    powNumberSingleThread(doubleMatrix, 2, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    powNumberSingleThread(intMatrix, 2, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    powNumberSingleThread(intMatrix, 2, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    numberPowSingleThread(2, doubleMatrix, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, std::pow(2, -1));
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    numberPowSingleThread(2, doubleMatrix, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, static_cast<int>(std::pow(2, -1)));
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    numberPowSingleThread(2, intMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, std::pow(2, -1));
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    numberPowSingleThread(2, intMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, static_cast<int>(std::pow(2, -1)));
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    addSingleThread(1, doubleMatrix, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 0.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    addSingleThread(1, doubleMatrix, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    addSingleThread(1, intMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 0.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    addSingleThread(1, intMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    subtractSingleThread(1, doubleMatrix, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    subtractSingleThread(1, doubleMatrix, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    subtractSingleThread(1, intMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    subtractSingleThread(1, intMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    subtractSingleThread(doubleMatrix, 1, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    subtractSingleThread(doubleMatrix, 1, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    subtractSingleThread(intMatrix, 1, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    subtractSingleThread(intMatrix, 1, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    multiplySingleThread(-1, doubleMatrix, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    multiplySingleThread(-1, doubleMatrix, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    multiplySingleThread(-1, intMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    multiplySingleThread(-1, intMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));

    divideSingleThread(-1, doubleMatrix, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    divideSingleThread(-1, doubleMatrix, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    divideSingleThread(-1, intMatrix, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    divideSingleThread(-1, intMatrix, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    divideSingleThread(doubleMatrix, 3, doubleOutput, 0, doubleMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    divideSingleThread(doubleMatrix, 3, intOutput, 0, doubleMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
    divideSingleThread(intMatrix, 3, doubleOutput, 0, intMatrix.size());
    doubleResult = Matrix<>(Shape{3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, doubleOutput.size()));
    divideSingleThread(intMatrix, 3, intOutput, 0, intMatrix.size());
    intResult = Matrix<int>(Shape{3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, intOutput.size()));
}
}  // namespace test
}  // namespace mca
