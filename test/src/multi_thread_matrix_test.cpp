#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <random>

#include "mca/__mca_internal/single_thread_matrix_calculation.h"
#include "mca/diag.h"
#include "mca/identity_matrix.h"
#include "mca/matrix.h"
#include "mca/mca.h"

using namespace std::chrono;

namespace mca {
namespace test {
class TestMatrixMultiThread : public testing::Test {
protected:
    static constexpr int MAX_VALUE  = 9;
    static constexpr int THREAD_NUM = 10;
    std::default_random_engine generator;
    Shape squareShape{1000, 1000};
    Shape rectangleShape{100, 121};
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    ASSERT_EQ(m1, n1);
    ASSERT_EQ(m2, n2);
    ASSERT_EQ(m3, n3);
    ASSERT_EQ(m4, n4);
    ASSERT_EQ(m5, n5);
    ASSERT_EQ(m6, n6);
    ASSERT_EQ(m7, n7);
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

    ASSERT_EQ(m1, n1);
    ASSERT_EQ(m2, n2);
    ASSERT_EQ(m3, n3);
    ASSERT_EQ(m4, n4);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
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

    ASSERT_EQ(m1, n1);
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

    ASSERT_EQ(singleOutput, multiOutput);
    ASSERT_EQ(a.shape(), Shape(0, 0));
    ASSERT_EQ(b.shape(), Shape(2, 0));
    ASSERT_EQ(a.data(), nullptr);
    ASSERT_EQ(b.data(), nullptr);
}

TEST_F(TestMatrixMultiThread, assignmentFromVector) {
    // create a null matrix
    a = Matrix<>(std::vector<std::vector<double>>{});
    // create a column null matirx
    b = Matrix<>(std::vector<std::vector<double>>{{}, {}});

    ASSERT_EQ(a.shape(), Shape(0, 0));
    ASSERT_EQ(b.shape(), Shape(2, 0));
    ASSERT_EQ(a.data(), nullptr);
    ASSERT_EQ(b.data(), nullptr);
}

TEST_F(TestMatrixMultiThread, transpose) {
    a = Matrix<>(rectangleShape);
    for (size_t i = 0; i < a.rows(); i++) {
        for (size_t j = 0; j < a.columns(); j++) { a.get(i, j) = generator() % MAX_VALUE; }
    }

    auto startTime     = high_resolution_clock::now();
    singleOutput       = a.transpose();
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
    multiOutput   = a.transpose();
    endTime       = high_resolution_clock::now();
    executionTime = duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // record multi-thread time in gtest
    testing::Test::RecordProperty("MultiTime", executionTime);

    // make sure they are equal
    ASSERT_EQ(singleOutput, multiOutput);
}

}  // namespace test
}  // namespace mca
