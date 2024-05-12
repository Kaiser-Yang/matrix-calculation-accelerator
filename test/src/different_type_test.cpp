#include <gtest/gtest.h>

#include "single_thread_matrix_calculation.h"

namespace mca {
namespace test {
class TestDifferentType : public testing::Test {
protected:
    Matrix<> doubleMatrix, doubleOutput, doubleResult;
    Matrix<int> intMatrix, intOutput, intResult;

    void SetUp() override {
        doubleMatrix = Matrix<>({3, 3}, -1.);
        doubleOutput = Matrix<>({3, 3}, 0.);
        intMatrix    = Matrix<int>({3, 3}, -1);
        intOutput    = Matrix<int>({3, 3}, 0);
    }

    void TearDown() override {}
};

TEST_F(TestDifferentType, differentTypeComparison) {
    ASSERT_TRUE(equalSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
    ASSERT_FALSE(notEqualSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
    ASSERT_FALSE(lessSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
    ASSERT_TRUE(lessEqualSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
    ASSERT_FALSE(greaterSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
    ASSERT_TRUE(greaterEqualSingleThread(doubleMatrix, intMatrix, 0, 0, doubleMatrix.getShape()));
}

TEST_F(TestDifferentType, differentTypeCalculation) {
    addSingleThread(intMatrix, doubleMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    addSingleThread(intMatrix, doubleMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    subtractSingleThread(intMatrix, doubleMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    subtractSingleThread(intMatrix, doubleMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    multiplySingleThread(intMatrix, doubleMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 3.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    multiplySingleThread(intMatrix, doubleMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    powNumberSingleThread(doubleMatrix, 2, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    powNumberSingleThread(doubleMatrix, 2, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    powNumberSingleThread(intMatrix, 2, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    powNumberSingleThread(intMatrix, 2, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    numberPowSingleThread(2, doubleMatrix, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, std::pow(2, -1));
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    numberPowSingleThread(2, doubleMatrix, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, static_cast<int>(std::pow(2, -1)));
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    numberPowSingleThread(2, intMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, std::pow(2, -1));
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    numberPowSingleThread(2, intMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, static_cast<int>(std::pow(2, -1)));
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    addSingleThread(1, doubleMatrix, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 0.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    addSingleThread(1, doubleMatrix, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    addSingleThread(1, intMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 0.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    addSingleThread(1, intMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 0);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    subtractSingleThread(1, doubleMatrix, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    subtractSingleThread(1, doubleMatrix, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    subtractSingleThread(1, intMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    subtractSingleThread(1, intMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    subtractSingleThread(doubleMatrix, 1, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    subtractSingleThread(doubleMatrix, 1, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    subtractSingleThread(intMatrix, 1, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, -2.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    subtractSingleThread(intMatrix, 1, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, -2);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    multiplySingleThread(-1, doubleMatrix, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    multiplySingleThread(-1, doubleMatrix, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    multiplySingleThread(-1, intMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    multiplySingleThread(-1, intMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));

    divideSingleThread(-1, doubleMatrix, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    divideSingleThread(-1, doubleMatrix, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    divideSingleThread(-1, intMatrix, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, 1.);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    divideSingleThread(-1, intMatrix, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, 1);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    divideSingleThread(doubleMatrix, 3, doubleOutput, 0, 0, doubleMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    divideSingleThread(doubleMatrix, 3, intOutput, 0, 0, doubleMatrix.getShape());
    intResult = Matrix<int>({3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
    divideSingleThread(intMatrix, 3, doubleOutput, 0, 0, intMatrix.getShape());
    doubleResult = Matrix<>({3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(doubleOutput, doubleResult, 0, 0, doubleOutput.getShape()));
    divideSingleThread(intMatrix, 3, intOutput, 0, 0, intMatrix.getShape());
    intResult = Matrix<int>({3, 3}, -1. / 3);
    ASSERT_TRUE(equalSingleThread(intOutput, intResult, 0, 0, intOutput.getShape()));
}
}  // namespace test
}  // namespace mca
