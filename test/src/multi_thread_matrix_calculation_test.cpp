#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <random>

#include "mca/__mca_internal/single_thread_matrix_calculation.h"
#include "mca/matrix.h"
#include "mca/mca.h"

using namespace std::chrono;

namespace mca {
namespace test {
class TestMultiThreadCalculation : public testing::Test {
protected:
    static constexpr int MAX_VALUE  = 1000;
    static constexpr int THREAD_NUM = 10;
    Shape squareShape{1000, 1000};
    Shape smallShape{10, 10};
    Shape mul1Shape{100, 121};
    Shape mul2Shape{121, 100};
    Shape rectangleShape1{1000, 1210};
    Shape rectangleShape2{1210, 1000};
    Shape powShape{100, 100};
    std::default_random_engine generator;
    Matrix<double> singleOutput, multiOutput, a, b, c, mulA, mulB;

    void SetUp() override { generator.seed(time(nullptr)); }

    void TearDown() override { init(0); }
};

TEST_F(TestMultiThreadCalculation, numAddMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = number + a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = number + a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixAddNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a + number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = a + number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfAddNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    singleOutput += number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput += number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numSelfAddMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    number += singleOutput;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    number += multiOutput;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSubtractMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a - b;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = a - b;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfSubtractMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value1);

    a = Matrix<double>(squareShape, value2);

    auto startTime = high_resolution_clock::now();
    singleOutput -= a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput -= a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixAddMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a + b;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = a + b;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfAddMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value1);

    a = Matrix<double>(squareShape, value2);

    auto startTime = high_resolution_clock::now();
    singleOutput += a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput += a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixMultiplyMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    mulA = Matrix<double>(mul1Shape, value1);
    mulB = Matrix<double>(mul2Shape, value2);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = mulA * mulB;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = mulA * mulB;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfMultiplyMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(mul1Shape, value1);

    mulA = Matrix<double>(mul2Shape, value2);

    auto startTime = high_resolution_clock::now();
    singleOutput *= mulA;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput *= mulA;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixLessEqualMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_FALSE(a <= c);
    ASSERT_FALSE(c <= a);

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 <= value2, a <= b);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 <= value2, a <= b);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, numSubtractMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = number - a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = number - a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixDivideNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE + 1;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a / number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = a / number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfDivideNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE + 1;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    singleOutput /= number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput /= number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numSelfSubtractMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    number -= singleOutput;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    number -= multiOutput;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixGreaterEqualMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_FALSE(a <= c);
    ASSERT_FALSE(c <= a);

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 >= value2, a >= b);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 >= value2, a >= b);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, matrixSubtractNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a - number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime     = high_resolution_clock::now();
    multiOutput   = a - number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numDivideMatrix) {
    auto value = generator() % MAX_VALUE + 1, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = number / a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime     = high_resolution_clock::now();
    multiOutput   = number / a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfSubtractNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    auto startTime = high_resolution_clock::now();
    singleOutput -= number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime = high_resolution_clock::now();
    multiOutput -= number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numSelfDivideMatrix) {
    auto value = generator() % MAX_VALUE + 1, number = generator() % MAX_VALUE;
    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    auto startTime = high_resolution_clock::now();
    number /= singleOutput;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime = high_resolution_clock::now();
    number /= multiOutput;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, transposeMatrix) {
    singleOutput = multiOutput = Matrix<double>(rectangleShape1);
    for (size_t i = 0; i < singleOutput.rows(); i++) {
        for (size_t j = 0; j < singleOutput.columns(); j++) {
            singleOutput.get(i, j) = multiOutput.get(i, j) = generator() % MAX_VALUE;
        }
    }
    auto startTime = high_resolution_clock::now();
    transpose(singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    transpose(multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, transposeMatrixToOutput) {
    singleOutput = multiOutput = Matrix<double>(rectangleShape2);

    a = Matrix<double>(rectangleShape1);

    for (size_t i = 0; i < a.rows(); i++) {
        for (size_t j = 0; j < a.columns(); j++) { a.get(i, j) = generator() % MAX_VALUE; }
    }

    auto startTime = high_resolution_clock::now();
    transpose(a, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    transpose(a, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, pow) {
    auto value = generator() % MAX_VALUE, exponent = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    pow(singleOutput, exponent);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    pow(multiOutput, exponent);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, powToOutput) {
    auto value = generator() % MAX_VALUE, exponent = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(powShape);

    a = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    pow(a, exponent, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    pow(a, exponent, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numberPowMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    numberPow(number, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    numberPow(number, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numberPowMatrixToOutput) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    a = singleOutput = multiOutput = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    numberPow(number, a, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    numberPow(number, a, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, powNumberMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    powNumber(singleOutput, number);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    powNumber(multiOutput, number);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, powNumberMatrixToOutput) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    a = singleOutput = multiOutput = Matrix<double>(powShape, value);

    auto startTime = high_resolution_clock::now();
    powNumber(a, number, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread transpose in multiOutput
    powNumber(a, number, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixLessMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_FALSE(a < c);
    ASSERT_FALSE(c < a);

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 < value2, a < b);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 < value2, a < b);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, matrixEqualMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_FALSE(a == c);
    ASSERT_FALSE(c == a);

    // make sure we can trigger operator== to return true
    c = a;

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 == value2, a == b);
    ASSERT_EQ(value1 == value2, b == a);
    ASSERT_EQ(a, c);
    ASSERT_EQ(c, a);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 == value2, a == b);
    ASSERT_EQ(value1 == value2, b == a);
    ASSERT_EQ(a, c);
    ASSERT_EQ(c, a);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, matrixNotEqualMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_NE(a, c);
    ASSERT_NE(c, a);

    // make sure we can trigger operator!= to return false
    c = a;

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 != value2, a != b);
    ASSERT_EQ(value1 != value2, b != a);
    ASSERT_FALSE(a != c);
    ASSERT_FALSE(c != a);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 != value2, a != b);
    ASSERT_EQ(value1 != value2, b != a);
    ASSERT_FALSE(a != c);
    ASSERT_FALSE(c != a);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, matrixGreaterMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<double>(squareShape, value1);
    b = Matrix<double>(squareShape, value2);
    c = Matrix<double>(smallShape, value1);

    // judgement of different shapes
    ASSERT_FALSE(a > c);
    ASSERT_FALSE(c > a);

    auto startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 > value2, a > b);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    ASSERT_EQ(value1 > value2, a > b);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);
}

TEST_F(TestMultiThreadCalculation, matrixMultiplyNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a * number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime     = high_resolution_clock::now();
    multiOutput   = a * number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numMultiplyMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<double>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = number * a;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime     = high_resolution_clock::now();
    multiOutput   = number * a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, numSelfMultiplyMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    number *= singleOutput;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    number *= multiOutput;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

TEST_F(TestMultiThreadCalculation, matrixSelfMultiplyNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<double>(squareShape, value);

    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    singleOutput *= number;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput *= number;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}
}  // namespace test
}  // namespace mca
