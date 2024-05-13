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
public:
    Matrix<> singleThread, multiThread;
    std::default_random_engine generator;

protected:
    void SetUp() override {
        generator.seed(time(nullptr));
        // initialize mca
        init();
        // create a large matrix
        singleThread = Matrix<>({3000, 30000}, 0);
        multiThread  = Matrix<>({3000, 30000}, 0);
    }

    void TearDown() override {}
};

TEST_F(TestMatrixMultiThread, fill) {
    Matrix<>::ElementType newValue = generator();
    // first use fill to get the single mode time
    auto startTime = high_resolution_clock::now();
    std::fill(singleThread.dataPtr(), singleThread.dataPtr() + singleThread.size(), newValue);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / threadNum());

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiThread.fill(newValue);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record thread number and time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    // ASSERT_TRUE(equalSingleThread(singleThread, multiThread, 0, 0, singleThread.getShape()));
}
}  // namespace test
}  // namespace mca
