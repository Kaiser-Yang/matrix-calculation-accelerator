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
class TestMatrixMultiThread : public testing::Test {
protected:
    std::default_random_engine generator;
    Shape shape{9000, 9000};
    Matrix<int>::ElementType value = generator();
    std::vector<std::vector<int>> vec =
        std::vector<std::vector<int>>(shape.rows, std::vector<int>(shape.columns, value));
    std::vector<int> array   = std::vector<int>(shape.size(), value);
    std::vector<int> diag    = std::vector(shape.rows, value);
    Matrix<int> singleThread = Matrix<>(shape, value);
    Matrix<int> multiThread  = Matrix<>(shape, value);
    size_t exponent          = 10;
    Shape powShape{200, 200};

    void SetUp() override { generator.seed(time(nullptr)); }

    void TearDown() override {}
};

TEST_F(TestMatrixMultiThread, fill) {
    // first use fill to get the single mode time
    auto startTime = high_resolution_clock::now();
    std::fill(singleThread.dataPtr(), singleThread.dataPtr() + singleThread.size(), value);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiThread.fill(value);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    // ASSERT_TRUE(equalSingleThread(singleThread, multiThread, 0, 0, singleThread.shape()));
}

TEST_F(TestMatrixMultiThread, constructors) {
    // single thread mode
    auto startTime = high_resolution_clock::now();
    // construct a matrix with a specified value
    Matrix<int> m1(shape, -1);

    // construct an identity matrix
    Matrix<int> m2(shape);

    // construct from a pointer
    Matrix<int> m3(shape, array.data(), array.size());

    // construct from a vector
    Matrix<int> m4(vec);

    // construct a diagonal matrix
    Matrix<int> m5(diag);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // multi thread mode
    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));
    startTime = high_resolution_clock::now();
    // construct a matrix with a specified value
    Matrix<int> n1(shape, -1);

    // construct an identity matrix
    Matrix<int> n2(shape);

    // construct from a pointer
    Matrix<int> n3(shape, array.data(), array.size());

    // construct from a vector
    Matrix<int> n4(vec);

    // construct a diagonal matrix
    Matrix<int> n5(diag);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check n1~n6 are equal with m1~m6
}

TEST_F(TestMatrixMultiThread, assignments) {
    Matrix<int> n, m;

    // single assignment thread mode
    auto startTime = high_resolution_clock::now();
    // copy from a Matrix<int>
    n = singleThread;
    // copy assignment from a pointer
    n = array.data();
    // copy assignment from a std::vector
    n                  = vec;
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // multi thread mode
    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));
    startTime = high_resolution_clock::now();
    // copy from a Matrix<int>
    m = multiThread;
    // copy assignment from a pointer
    m = array.data();
    // copy assignment from a std::vector
    m             = vec;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check n are equal with m
}

TEST_F(TestMatrixMultiThread, powNumber) {
    Matrix<int> output = {shape, -1};
    // first use powNumberSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    powNumberSingleThread(singleThread, 2, output, 0, singleThread.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    multiThread.powNumber(2);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiThread, 0, output.size()));
}

TEST_F(TestMatrixMultiThread, powNumberToOutput) {
    Matrix<int> output      = {shape, -1};
    Matrix<int> multiOutput = {shape, -1};
    // first use powNumberSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    powNumberSingleThread(singleThread, 2, output, 0, singleThread.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multi_output
    multiThread.powNumber(2, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiOutput, 0, output.size()));
}

TEST_F(TestMatrixMultiThread, numberPow) {
    Matrix<int> output = {shape, -1};
    // first use numberPowSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    numberPowSingleThread(2, singleThread, output, 0, singleThread.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    multiThread.numberPow(2);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiThread, 0, output.size()));
}

TEST_F(TestMatrixMultiThread, numberPowToOutput) {
    Matrix<int> output      = {shape, -1};
    Matrix<int> multiOutput = {shape, -1};
    // first use numberPowSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    numberPowSingleThread(2, singleThread, output, 0, singleThread.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multi_output
    multiThread.numberPow(2, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiOutput, 0, output.size()));
}

TEST_F(TestMatrixMultiThread, pow) {
    Matrix<int> output(powShape);
    Matrix<int> a(powShape, 1);
    auto startTime = high_resolution_clock::now();
    for (size_t i = 0; i < exponent; i++) { output *= a; }
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    a.pow(exponent);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, a, 0, output.size()));
}

TEST_F(TestMatrixMultiThread, powToOutput) {
    Matrix<int> output(powShape);
    Matrix<int> multiOutput(powShape);
    Matrix<int> a(powShape, 1);
    auto startTime = high_resolution_clock::now();
    for (size_t i = 0; i < exponent; i++) { output *= a; }
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multi_output
    a.pow(exponent, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiOutput, 0, output.size()));
}
}  // namespace test
}  // namespace mca
