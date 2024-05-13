#include "single_thread_matrix_calculation.h"

#include <gtest/gtest.h>

#include <cmath>

#include "matrix.h"

namespace mca {
namespace test {
class TestSinglThreadCalculation : public testing::Test {
protected:
    Matrix<> one, negOne, output, a, b, c, d, sym, antisym;
    Matrix<int> e;

    void SetUp() override {
        one     = Matrix<>({3, 3}, 1);
        negOne  = Matrix<>({3, 3}, -1);
        a       = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        b       = Matrix<>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
        c       = Matrix<>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        d       = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        e       = Matrix<int>({{1, 2, 3}, {2, 3, 4}, {6, 6, 6}});
        sym     = Matrix<>({{1, 2. / 3, 3. / 5}, {4. / 6, 3, 8. / 6}, {1.5 / 2.5, 4. / 3, 5}});
        antisym = Matrix<>({{1, -2. / 3, -3. / 5}, {4. / 6, 3, -8. / 6}, {1.5 / 2.5, 4. / 3, 5}});
    }

    void TearDown() override {}
};

TEST_F(TestSinglThreadCalculation, powNumberWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    powNumberSingleThread(a, 2, output, 0, 0, a.getShape());
    Matrix<> result = Matrix<>({{0, 0, 0}, {1, 1, 1}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, powNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    powNumberSingleThread(c, 2, output, 0, 1, {2, 2});
    Matrix<> result = Matrix<>({{-1, 4, 9}, {-1, 25, 36}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, numberPowWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    numberPowSingleThread(2, a, output, 0, 0, a.getShape());
    Matrix<> result = Matrix<>({{1, 1, 1}, {2, 2, 2}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, numberPowSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    numberPowSingleThread(2, c, output, 0, 1, {2, 2});
    Matrix<> result({{-1, 4, 8}, {-1, 32, 64}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessWholeMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 0, 0, a.getShape()));
    ASSERT_FALSE(lessSingleThread(a, b, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessSubMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 1, 0, {2, 3}));
    ASSERT_FALSE(lessSingleThread(a, b, 1, 0, {2, 2}));
}

TEST_F(TestSinglThreadCalculation, equalWholeMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 0, 0, a.getShape()));
    ASSERT_FALSE(equalSingleThread(a, b, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, equalSubMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 1, 0, {2, 2}));
    ASSERT_FALSE(equalSingleThread(a, b, 1, 0, {2, 2}));
}

TEST_F(TestSinglThreadCalculation, lessEqualWholeMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 0, 0, a.getShape()));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 0, 0, a.getShape()));
    ASSERT_FALSE(lessEqualSingleThread(c, b, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, lessEqualSubMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 0, 0, {2, 3}));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 0, 0, {2, 3}));
    ASSERT_FALSE(lessEqualSingleThread(c, a, 0, 0, {2, 3}));
}

TEST_F(TestSinglThreadCalculation, greaterWholeMatrix) {
    ASSERT_TRUE(greaterSingleThread(c, a, 0, 0, c.getShape()));
    ASSERT_FALSE(greaterSingleThread(d, a, 0, 0, d.getShape()));
    ASSERT_FALSE(greaterSingleThread(d, b, 0, 0, b.getShape()));
}

TEST_F(TestSinglThreadCalculation, greaterSubMatrix) {
    ASSERT_TRUE(greaterSingleThread(c, a, 0, 1, {2, 2}));
    ASSERT_FALSE(greaterSingleThread(a, b, 0, 1, {2, 2}));
    ASSERT_FALSE(greaterSingleThread(a, d, 0, 1, {2, 2}));
}

TEST_F(TestSinglThreadCalculation, greaterEqualWholeMatrix) {
    ASSERT_TRUE(greaterEqualSingleThread(a, d, 0, 0, a.getShape()));
    ASSERT_TRUE(greaterEqualSingleThread(c, a, 0, 0, c.getShape()));
    ASSERT_FALSE(greaterEqualSingleThread(b, c, 0, 0, b.getShape()));
}

TEST_F(TestSinglThreadCalculation, greaterEqualSubMatrix) {
    ASSERT_TRUE(greaterEqualSingleThread(a, d, 0, 1, {3, 2}));
    ASSERT_TRUE(greaterEqualSingleThread(c, b, 0, 1, {3, 2}));
    ASSERT_FALSE(greaterEqualSingleThread(b, c, 0, 1, {3, 2}));
}

TEST_F(TestSinglThreadCalculation, notEqualWholeMatrix) {
    ASSERT_TRUE(notEqualSingleThread(a, c, 0, 0, a.getShape()));
    ASSERT_FALSE(notEqualSingleThread(a, d, 0, 0, a.getShape()));
}

TEST_F(TestSinglThreadCalculation, notEqualSubMatrix) {
    ASSERT_TRUE(notEqualSingleThread(a, c, 1, 1, {2, 1}));
    ASSERT_FALSE(notEqualSingleThread(a, d, 1, 1, {2, 1}));
}

TEST_F(TestSinglThreadCalculation, addNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(2, a, output, 0, 0, a.getShape());
    Matrix<> result({{2, 2, 2}, {3, 3, 3}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, {3, 3}));
}

TEST_F(TestSinglThreadCalculation, addNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(2, a, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 3, 3}, {-1, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, {3, 3}));
}

TEST_F(TestSinglThreadCalculation, subtractNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, 1, output, 0, 0, a.getShape());
    Matrix<> result({{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, {3, 3}));

    Matrix<int> output2({3, 3}, -1);
    subtractSingleThread(9, e, output2, 0, 0, a.getShape());
    Matrix<> result2({{8, 7, 6}, {7, 6, 5}, {3, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output2, result2, 0, 0, {3, 3}));
}

TEST_F(TestSinglThreadCalculation, subtractNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, 1, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 0, 0}, {-1, 1, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, {3, 3}));

    Matrix<int> output2({3, 3}, -1);
    subtractSingleThread(9, e, output2, 1, 0, {2, 3});
    Matrix<> result2({{-1, -1, -1}, {7, 6, 5}, {3, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output2, result2, 0, 0, {3, 3}));
}

TEST_F(TestSinglThreadCalculation, multiplyNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(3, c, output, 0, 0, c.getShape());
    Matrix<> result({{3, 6, 9}, {12, 15, 18}, {21, 24, 27}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, multiplyNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(3, c, output, 1, 0, {2, 3});
    Matrix<> result({{-1, -1, -1}, {12, 15, 18}, {21, 24, 27}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, divideNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    divideSingleThread(c, 3, output, 0, 0, c.getShape());
    Matrix<> result({{1. / 3, 2. / 3, 1}, {4. / 3, 5. / 3, 2}, {7. / 3, 8. / 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    output = Matrix<>({3, 3}, -1);
    divideSingleThread(9, c, output, 0, 0, c.getShape());
    Matrix<> result2({{9, 9. / 2, 3}, {9. / 4, 9. / 5, 9. / 6}, {9. / 7, 9. / 8, 1}});
    ASSERT_TRUE(equalSingleThread(output, result2, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, divideNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    divideSingleThread(c, 3, output, 1, 0, {2, 3});
    Matrix<> result({{-1, -1, -1}, {4. / 3, 5. / 3, 2}, {7. / 3, 8. / 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    output = Matrix<>({3, 3}, -1);
    divideSingleThread(9, c, output, 1, 0, {2, 3});
    Matrix<> result2({{-1, -1, -1}, {9. / 4, 9. / 5, 9. / 6}, {9. / 7, 9. / 8, 1}});
    ASSERT_TRUE(equalSingleThread(output, result2, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, addWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    addSingleThread(a, b, output, 0, 0, a.getShape());
    Matrix<> result({{1, 0, 0}, {1, 2, 1}, {2, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    addSingleThread(b, a, output, 0, 0, b.getShape());
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, addSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(a, b, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 2, 1}, {-1, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    addSingleThread(b, a, output, 1, 1, {2, 2});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, sustractWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    subtractSingleThread(a, b, output, 0, 0, a.getShape());
    Matrix<> result({{-1, 0, 0}, {1, 0, 1}, {2, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    subtractSingleThread(b, a, output, 0, 0, b.getShape());
    result = Matrix<>({{1, 0, 0}, {-1, 0, -1}, {-2, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, sustractSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, b, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 0, 1}, {-1, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    subtractSingleThread(b, a, output, 1, 1, {2, 2});
    result = Matrix<>({{-1, -1, -1}, {-1, 0, -1}, {-1, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, multiplyWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    multiplySingleThread(a, one, output, 0, 0, a.getShape());
    Matrix<> result({{0, 0, 0}, {3, 3, 3}, {6, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    multiplySingleThread(one, a, output, 0, 0, one.getShape());
    result = Matrix<>({3, 3}, 3);
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, multiplySubMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(a, one, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 3, 3}, {-1, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));

    multiplySingleThread(one, a, output, 1, 1, {2, 2});
    result = Matrix<>({{-1, -1, -1}, {-1, 3, 3}, {-1, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, transposeWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    transposeSingleThread(c, output, 0, 0, c.getShape());
    Matrix<> result({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, transposeSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    transposeSingleThread(c, output, 1, 1, {2, 2});
    Matrix<> result({{-1, -1, -1}, {-1, 5, 8}, {-1, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, 0, output.getShape()));
}

TEST_F(TestSinglThreadCalculation, symmetricWholeMatrix) {
    ASSERT_TRUE(symmetricSingleThread(sym, 0, 3));
    ASSERT_FALSE(symmetricSingleThread(antisym, 0, 3));
}

TEST_F(TestSinglThreadCalculation, symmetricSubMatrix) {
    ASSERT_TRUE(symmetricSingleThread(sym, 1, 2));
    ASSERT_FALSE(symmetricSingleThread(antisym, 1, 2));
}

TEST_F(TestSinglThreadCalculation, antisymmetricWholeMatrix) {
    ASSERT_TRUE(antisymmetricSingleThread(antisym, 0, 3));
    ASSERT_FALSE(antisymmetricSingleThread(sym, 0, 3));
}

TEST_F(TestSinglThreadCalculation, antisymmetricSubMatrix) {
    ASSERT_TRUE(antisymmetricSingleThread(antisym, 0, 1));
    ASSERT_FALSE(antisymmetricSingleThread(sym, 0, 1));
}

}  // namespace test
}  // namespace mca
