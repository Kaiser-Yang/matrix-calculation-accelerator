#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <random>

#include "matrix.h"
#include "mca.h"
#include "single_thread_matrix_calculation.h"

using namespace std::chrono;

namespace mca {
namespace test {
class TestMultiThreadCalculation : public testing::Test {
protected:
    static constexpr int MAX_VALUE  = 1000;
    static constexpr int THREAD_NUM = 10;
    Shape squareShape{1000, 1000};
    Shape mul1Shape{100, 121};
    Shape mul2Shape{121, 100};
    std::default_random_engine generator;
    Matrix<> singleOutput, multiOutput, a, b, mulA, mulB;

    void SetUp() override { generator.seed(time(nullptr)); }

    void TearDown() override { init(0); }
};

TEST_F(TestMultiThreadCalculation, numAddMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixAddNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfAddNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, numSelfAddMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSubtractMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<>(squareShape, value1);
    b = Matrix<>(squareShape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfSubtractMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape, value1);

    a = Matrix<>(squareShape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixAddMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    a = Matrix<>(squareShape, value1);
    b = Matrix<>(squareShape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfAddMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape, value1);

    a = Matrix<>(squareShape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixMultiplyMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    mulA = Matrix<>(mul1Shape, value1);
    mulB = Matrix<>(mul2Shape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfMultiplyMatrix) {
    auto value1 = generator() % MAX_VALUE, value2 = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(mul1Shape, value1);

    mulA = Matrix<>(mul2Shape, value2);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixGreaterEqualMatrix) {
    auto value1     = generator() % MAX_VALUE;
    auto value2     = value1 + (generator() % MAX_VALUE) + 1;
    a               = Matrix<>(squareShape, value1);
    b               = Matrix<>(squareShape, value2);
    bool flagSingle = false, flagMultiGreater = false, flagMultiEqual = false;

    auto startTime     = high_resolution_clock::now();
    flagSingle         = (b >= a);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTimeGreater", executionTime / (threadNum() + 1));

    startTime        = high_resolution_clock::now();
    flagMultiGreater = (b >= a);
    endTime          = high_resolution_clock::now();
    executionTime    = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    testing::Test::RecordProperty("MultiTimeGreater", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTimeEqual", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime      = high_resolution_clock::now();
    flagMultiEqual = (a >= a);
    endTime        = high_resolution_clock::now();
    executionTime  = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTimeEqual", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(flagSingle);
    ASSERT_TRUE(flagMultiGreater);
    ASSERT_TRUE(flagMultiEqual);
}

TEST_F(TestMultiThreadCalculation, matrixSubtractNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, numDivideMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    a = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfSubtractNum) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    singleOutput = multiOutput = Matrix<>(squareShape, value);

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

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMultiThreadCalculation, numSelfDivideMatrix) {
    auto value = generator() % MAX_VALUE, number = generator() % MAX_VALUE;
    singleOutput = multiOutput = Matrix<>(squareShape, value);

    auto startTime     = high_resolution_clock::now();
    singleOutput       = number / singleOutput;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    startTime     = high_resolution_clock::now();
    multiOutput   = number / multiOutput;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

}  // namespace test
}  // namespace mca
