#include <gtest/gtest.h>

#include <chrono>

#include "matrix.h"
#include "mca.h"
#include "single_thread_matrix_calculation.h"
using namespace std::chrono;

namespace mca {
namespace test {
class TestMultiThreadCalculation : public testing::Test {
protected:
    Shape shape{9000, 9000};
    Matrix<> output, a;
    void SetUp() override { a = Matrix<>(shape, 123); }
    void TearDown() override {}
};

TEST_F(TestMultiThreadCalculation, numAddMatrix) {
    output = Matrix<>{shape, -1};
    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    addSingleThread(3, a, output, 0, a.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime              = high_resolution_clock::now();
    auto multiThreadOutput = 3 + a;
    endTime                = high_resolution_clock::now();
    executionTime          = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiThreadOutput, 0, output.size()));
}

TEST_F(TestMultiThreadCalculation, matrixAddNum) {
    output = Matrix<>{shape, -1};
    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    addSingleThread(3, a, output, 0, a.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime              = high_resolution_clock::now();
    auto multiThreadOutput = a + 3;
    endTime                = high_resolution_clock::now();
    executionTime          = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, multiThreadOutput, 0, output.size()));
}

TEST_F(TestMultiThreadCalculation, matrixSelfAddNum) {
    output = Matrix<>{shape, -1};
    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    addSingleThread(3, a, output, 0, a.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    a += 3;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, a, 0, a.size()));
}

TEST_F(TestMultiThreadCalculation, numSelfAddMatrix) {
    output = Matrix<>{shape, -1};
    // first use addSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    addSingleThread(3, a, output, 0, a.size());
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init();

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    3 += a;
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(output, a, 0, a.size()));
}

}  // namespace test
}  // namespace mca
