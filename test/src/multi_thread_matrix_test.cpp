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
    testing::Test::RecordProperty("BaseTime", executionTime / threadNum());

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiThread.fill(value);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    // ASSERT_TRUE(equalSingleThread(singleThread, multiThread, 0, 0, singleThread.getShape()));
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
    testing::Test::RecordProperty("BaseTime", executionTime / threadNum());
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
    testing::Test::RecordProperty("BaseTime", executionTime / threadNum());
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
}  // namespace test
}  // namespace mca
