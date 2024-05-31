#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <random>

// #include "diag.h"
#include "identity_matrix.h"
#include "matrix.h"
#include "mca.h"
#include "single_thread_matrix_calculation.h"

using namespace std::chrono;

namespace mca {
namespace test {
class TestMatrixMultiThread : public testing::Test {
protected:
    static constexpr int MAX_VALUE  = 9;
    static constexpr int THREAD_NUM = 10;
    std::default_random_engine generator;
    Shape squareShape{1000, 1000};
    std::vector<std::vector<double>> vec;
    std::vector<double> array;
    std::vector<double> diag;
    Matrix<> a, b;
    Matrix<> singleOutput, multiOutput;
    size_t exponent;
    Shape powShape{100, 100};

    void SetUp() override {
        generator.seed(time(nullptr));
        exponent = generator() % MAX_VALUE;
    }

    void TearDown() override { init(0); }
};

TEST_F(TestMatrixMultiThread, fill) {
    auto value = generator() % MAX_VALUE;
    // first use fill before init(THREAD_NUM), this will run in single-thread mode
    auto startTime = high_resolution_clock::now();
    singleOutput.fill(value);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    multiOutput.fill(value);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, constructors) {
    auto value = generator() % MAX_VALUE;

    a = Matrix<>(squareShape, value);

    vec   = std::vector<std::vector<double>>(squareShape.rows,
                                           std::vector<double>(squareShape.columns, value));
    array = std::vector<double>(squareShape.size() / 2, value);
    diag  = std::vector<double>(squareShape.rows, value);

    // single thread mode
    auto startTime = high_resolution_clock::now();
    // construct a matrix with a specified value
    Matrix<> m1(squareShape, value);

    // construct an identity matrix
    Matrix<> m2(squareShape, IdentityMatrix());

    // construct from a pointer
    Matrix<> m3(squareShape, array.data(), array.size());

    // construct from a vector
    Matrix<> m4(vec);

    // construct a diagonal matrix
    Matrix<> m5(Diag(diag));

    // copy constructor
    Matrix<> m6(a);
    Matrix<> m7(Matrix<int>(squareShape, value));
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);

    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // multi thread mode
    startTime = high_resolution_clock::now();
    // construct a matrix with a specified value
    Matrix<> n1(squareShape, value);

    // construct an identity matrix
    Matrix<> n2(squareShape, IdentityMatrix());

    // construct from a pointer
    Matrix<> n3(squareShape, array.data(), array.size());

    // construct from a vector
    Matrix<> n4(vec);

    // construct a diagonal matrix
    Matrix<> n5(Diag(diag));

    // copy constructor
    Matrix<> n6(a);
    Matrix<> n7(Matrix<int>(squareShape, value));
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check n1~n7 are equal with m1~m7
    ASSERT_TRUE(equalSingleThread(m1, n1, 0, m1.size()));
    ASSERT_TRUE(equalSingleThread(m2, n2, 0, m2.size()));
    ASSERT_TRUE(equalSingleThread(m3, n3, 0, m3.size()));
    ASSERT_TRUE(equalSingleThread(m4, n4, 0, m4.size()));
    ASSERT_TRUE(equalSingleThread(m5, n5, 0, m5.size()));
    ASSERT_TRUE(equalSingleThread(m6, n6, 0, m6.size()));
    ASSERT_TRUE(equalSingleThread(m7, n7, 0, m7.size()));
}

TEST_F(TestMatrixMultiThread, assignments) {
    auto value = generator() % MAX_VALUE;

    a = Matrix<>(squareShape, value);

    vec   = std::vector<std::vector<double>>(squareShape.rows,
                                           std::vector<double>(squareShape.columns, value));
    array = std::vector<double>(squareShape.size(), value);
    diag  = std::vector<double>(squareShape.rows, value);

    Matrix<> n1, n2, n3, n4, m1, m2, m3, m4;

    // single assignment thread mode
    auto startTime = high_resolution_clock::now();
    // copy from a Matrix<>
    n1 = a;
    // copy assignment from Matrix<int>
    n4                 = Matrix<int>(squareShape, value);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // multi thread mode
    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));
    startTime = high_resolution_clock::now();
    // copy from a Matrix<>
    m1 = a;
    // copy assignment from Matrix<int>
    m4            = Matrix<int>(squareShape, value);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check n1~n4 are equal with m1~m4
    ASSERT_TRUE(equalSingleThread(m1, n1, 0, m1.size()));
    ASSERT_TRUE(equalSingleThread(m2, n2, 0, m2.size()));
    ASSERT_TRUE(equalSingleThread(m3, n3, 0, m3.size()));
    ASSERT_TRUE(equalSingleThread(m4, n4, 0, m4.size()));
}

TEST_F(TestMatrixMultiThread, powNumber) {
    auto value = generator() % MAX_VALUE;

    const auto &number = exponent;

    singleOutput = multiOutput = Matrix<>(squareShape, value);

    auto startTime = high_resolution_clock::now();
    singleOutput.powNumber(number);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    multiOutput.powNumber(number);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, powNumberToOutput) {
    auto value = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape);

    const auto &number = exponent;

    a = Matrix<>(squareShape, value);

    auto startTime = high_resolution_clock::now();
    a.powNumber(number, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiOutput
    a.powNumber(number, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, numberPow) {
    auto value = generator() % MAX_VALUE;

    const auto &number = exponent;

    singleOutput = multiOutput = Matrix<>(squareShape, value);

    // first use numberPowSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    singleOutput.numberPow(number);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    multiOutput.numberPow(number);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, numberPowToOutput) {
    auto value = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(squareShape);

    const auto &number = exponent;

    a = Matrix<>(squareShape, value);
    // first use numberPowSingleThread to get the single mode time
    auto startTime = high_resolution_clock::now();
    a.numberPow(number, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiOutput
    a.numberPow(number, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, pow) {
    auto value = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(powShape, value);

    auto startTime = high_resolution_clock::now();
    singleOutput.pow(exponent);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiThread
    multiOutput.pow(exponent);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, powToOutput) {
    auto value = generator() % MAX_VALUE;

    singleOutput = multiOutput = Matrix<>(powShape);

    a = Matrix<>(powShape, value);

    auto startTime = high_resolution_clock::now();
    a.pow(exponent, singleOutput);
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    init(THREAD_NUM);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));

    // get the multi-thread mode time
    startTime = high_resolution_clock::now();
    // get multi-thread pownumber in multiOutput
    a.pow(exponent, multiOutput);
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO this should be updated with Matrix::operator== with multi-thread
    // make sure they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
}

TEST_F(TestMatrixMultiThread, constructorFromDiag) {
    // single assignment thread mode
    auto startTime = high_resolution_clock::now();
    Matrix<int> n1(Diag({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // multi thread mode  set limit = 1
    init(THREAD_NUM, 1);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));
    startTime = high_resolution_clock::now();
    Matrix<int> m1(Diag({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check if they are equal
    ASSERT_TRUE(equalSingleThread(m1, n1, 0, m1.size()));
}

TEST_F(TestMatrixMultiThread, assignmentFromInitializerList) {
    // create a null matrix
    a = Matrix<>(std::initializer_list<std::initializer_list<double>>{});
    // create a column null matirx
    b = Matrix<>(std::initializer_list<std::initializer_list<double>>{{}, {}});

    auto startTime     = high_resolution_clock::now();
    singleOutput       = Matrix<>({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 5, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 6, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 9}});
    auto endTime       = high_resolution_clock::now();
    auto executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("SingleTime", executionTime);

    // multi thread mode
    init(THREAD_NUM, 1);
    // the expected time in multi thread
    testing::Test::RecordProperty("BaseTime", executionTime / (threadNum() + 1));
    startTime     = high_resolution_clock::now();
    multiOutput   = Matrix<>({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 5, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 6, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 9}});
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // TODO use operator== to check they are equal
    ASSERT_TRUE(equalSingleThread(singleOutput, multiOutput, 0, singleOutput.size()));
    ASSERT_EQ(a.shape(), Shape(0, 0));
    ASSERT_EQ(b.shape(), Shape(2, 0));
    ASSERT_EQ(a.dataPtr(), nullptr);
    ASSERT_EQ(b.dataPtr(), nullptr);
}

TEST_F(TestMatrixMultiThread, assignmentFromVector) {
    // create a null matrix
    a = Matrix<>(std::vector<std::vector<double>>{});
    // create a column null matirx
    b = Matrix<>(std::vector<std::vector<double>>{{}, {}});

    ASSERT_EQ(a.shape(), Shape(0, 0));
    ASSERT_EQ(b.shape(), Shape(2, 0));
    ASSERT_EQ(a.dataPtr(), nullptr);
    ASSERT_EQ(b.dataPtr(), nullptr);
}
}  // namespace test
}  // namespace mca
