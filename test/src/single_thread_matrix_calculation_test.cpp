#include "single_thread_matrix_calculation.h"

#include <gtest/gtest.h>

#include <cmath>

#include "matrix.h"

namespace mca {
namespace test {
class TestSingleThreadCalculation : public testing::Test {
protected:
    Matrix<> one, negOne, output, a, b, c, d, sym, antisym;
    Matrix<int> e, f;

    void SetUp() override {
        one     = Matrix<>({3, 3}, 1);
        negOne  = Matrix<>({3, 3}, -1);
        a       = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        b       = Matrix<>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
        c       = Matrix<>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        d       = Matrix<>({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}});
        e       = Matrix<int>({{1, 2, 3}, {2, 3, 4}, {6, 6, 6}});
        f       = Matrix<int>({{3, 2, 1}, {2, 3, 4}, {6, 6, 6}});
        sym     = Matrix<>({{1, 2. / 3, 3. / 5}, {4. / 6, 3, 8. / 6}, {1.5 / 2.5, 4. / 3, 5}});
        antisym = Matrix<>({{1, -2. / 3, -3. / 5}, {4. / 6, 3, -8. / 6}, {1.5 / 2.5, 4. / 3, 5}});
    }

    void TearDown() override {}
};

TEST_F(TestSingleThreadCalculation, powNumberWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    powNumberSingleThread(a, 2, output, 0, a.size());
    Matrix<> result = Matrix<>({{0, 0, 0}, {1, 1, 1}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, powNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    powNumberSingleThread(c, 2, output, 1, 5);
    Matrix<> result = Matrix<>({{-1, 4, 9}, {16, 25, 36}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, numberPowWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    numberPowSingleThread(2, a, output, 0, a.size());
    Matrix<> result = Matrix<>({{1, 1, 1}, {2, 2, 2}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, numberPowSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    numberPowSingleThread(2, c, output, 1, 5);
    Matrix<> result({{-1, 4, 8}, {16, 32, 64}, {-1, -1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, lessWholeMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 0, a.size()));
    ASSERT_FALSE(lessSingleThread(a, b, 0, a.size()));
}

TEST_F(TestSingleThreadCalculation, lessSubMatrix) {
    ASSERT_TRUE(lessSingleThread(a, c, 1, 3));
    ASSERT_FALSE(lessSingleThread(a, b, 3, 3));
}

TEST_F(TestSingleThreadCalculation, equalWholeMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 0, a.size()));
    ASSERT_FALSE(equalSingleThread(a, b, 0, a.size()));
    ASSERT_FALSE(equalSingleThread(e, f, 0, e.size()));
}

TEST_F(TestSingleThreadCalculation, equalSubMatrix) {
    ASSERT_TRUE(equalSingleThread(a, d, 1, 2));
    ASSERT_FALSE(equalSingleThread(a, b, 1, 3));
}

TEST_F(TestSingleThreadCalculation, lessEqualWholeMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 0, a.size()));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 0, a.size()));
    ASSERT_FALSE(lessEqualSingleThread(c, b, 0, c.size()));
}

TEST_F(TestSingleThreadCalculation, lessEqualSubMatrix) {
    ASSERT_TRUE(lessEqualSingleThread(a, c, 4, 4));
    ASSERT_TRUE(lessEqualSingleThread(a, d, 4, 4));
    ASSERT_FALSE(lessEqualSingleThread(c, a, 4, 4));
}

TEST_F(TestSingleThreadCalculation, greaterWholeMatrix) {
    ASSERT_TRUE(greaterSingleThread(c, a, 0, c.size()));
    ASSERT_FALSE(greaterSingleThread(d, a, 0, d.size()));
    ASSERT_FALSE(greaterSingleThread(d, b, 0, d.size()));
}

TEST_F(TestSingleThreadCalculation, greaterSubMatrix) {
    ASSERT_TRUE(greaterSingleThread(c, a, 2, 3));
    ASSERT_FALSE(greaterSingleThread(a, b, 2, 3));
    ASSERT_FALSE(greaterSingleThread(a, d, 2, 3));
}

TEST_F(TestSingleThreadCalculation, greaterEqualWholeMatrix) {
    ASSERT_TRUE(greaterEqualSingleThread(a, d, 0, a.size()));
    ASSERT_TRUE(greaterEqualSingleThread(c, a, 0, c.size()));
    ASSERT_FALSE(greaterEqualSingleThread(b, c, 0, b.size()));
}

TEST_F(TestSingleThreadCalculation, greaterEqualSubMatrix) {
    ASSERT_TRUE(greaterEqualSingleThread(a, d, 3, 6));
    ASSERT_TRUE(greaterEqualSingleThread(c, b, 3, 6));
    ASSERT_FALSE(greaterEqualSingleThread(b, c, 3, 6));
}

TEST_F(TestSingleThreadCalculation, notEqualWholeMatrix) {
    ASSERT_TRUE(notEqualSingleThread(a, c, 0, a.size()));
    ASSERT_FALSE(notEqualSingleThread(a, d, 0, a.size()));
}

TEST_F(TestSingleThreadCalculation, notEqualSubMatrix) {
    ASSERT_TRUE(notEqualSingleThread(a, c, 3, 6));
    ASSERT_FALSE(notEqualSingleThread(a, d, 3, 6));
}

TEST_F(TestSingleThreadCalculation, addNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(2, a, output, 0, a.size());
    Matrix<> result({{2, 2, 2}, {3, 3, 3}, {4, 4, 4}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, addNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(2, a, output, 4, 4);
    Matrix<> result({{-1, -1, -1}, {-1, 3, 3}, {4, 4, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, subtractNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, 1, output, 0, a.size());
    Matrix<> result({{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    Matrix<int> output2({3, 3}, -1);
    subtractSingleThread(9, e, output2, 0, a.size());
    Matrix<> result2({{8, 7, 6}, {7, 6, 5}, {3, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output2, result2, 0, output2.size()));
}

TEST_F(TestSingleThreadCalculation, subtractNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, 1, output, 4, 4);
    Matrix<> result({{-1, -1, -1}, {-1, 0, 0}, {1, 1, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    Matrix<int> output2({3, 3}, -1);
    subtractSingleThread(9, e, output2, 3, 6);
    Matrix<> result2({{-1, -1, -1}, {7, 6, 5}, {3, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output2, result2, 0, output2.size()));
}

TEST_F(TestSingleThreadCalculation, multiplyNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(3, c, output, 0, c.size());
    Matrix<> result({{3, 6, 9}, {12, 15, 18}, {21, 24, 27}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, multiplyNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(3, c, output, 3, 6);
    Matrix<> result({{-1, -1, -1}, {12, 15, 18}, {21, 24, 27}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, divideNumberWholeMatrix) {
    output = Matrix<>({3, 3}, -1);
    divideSingleThread(c, 3, output, 0, c.size());
    Matrix<> result({{1. / 3, 2. / 3, 1}, {4. / 3, 5. / 3, 2}, {7. / 3, 8. / 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    output = Matrix<>({3, 3}, -1);
    divideSingleThread(9, c, output, 0, c.size());
    Matrix<> result2({{9, 9. / 2, 3}, {9. / 4, 9. / 5, 9. / 6}, {9. / 7, 9. / 8, 1}});
    ASSERT_TRUE(equalSingleThread(output, result2, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, divideNumberSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    divideSingleThread(c, 3, output, 3, 6);
    Matrix<> result({{-1, -1, -1}, {4. / 3, 5. / 3, 2}, {7. / 3, 8. / 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    output = Matrix<>({3, 3}, -1);
    divideSingleThread(9, c, output, 3, 6);
    Matrix<> result2({{-1, -1, -1}, {9. / 4, 9. / 5, 9. / 6}, {9. / 7, 9. / 8, 1}});
    ASSERT_TRUE(equalSingleThread(output, result2, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, addWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    addSingleThread(a, b, output, 0, a.size());
    Matrix<> result({{1, 0, 0}, {1, 2, 1}, {2, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    addSingleThread(b, a, output, 0, b.size());
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, addSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    addSingleThread(a, b, output, 3, 6);
    Matrix<> result({{-1, -1, -1}, {1, 2, 1}, {2, 2, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    addSingleThread(b, a, output, 3, 6);
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, sustractWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    subtractSingleThread(a, b, output, 0, a.size());
    Matrix<> result({{-1, 0, 0}, {1, 0, 1}, {2, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    subtractSingleThread(b, a, output, 0, b.size());
    result = Matrix<>({{1, 0, 0}, {-1, 0, -1}, {-2, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, sustractSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    subtractSingleThread(a, b, output, 3, 6);
    Matrix<> result({{-1, -1, -1}, {1, 0, 1}, {2, 2, 1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    subtractSingleThread(b, a, output, 3, 6);
    result = Matrix<>({{-1, -1, -1}, {-1, 0, -1}, {-2, -2, -1}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, multiplyWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    multiplySingleThread(a, one, output, 0, a.size());
    Matrix<> result({{0, 0, 0}, {3, 3, 3}, {6, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    multiplySingleThread(one, a, output, 0, one.size());
    result = Matrix<>({3, 3}, 3);
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, multiplySubMatrix) {
    output = Matrix<>({3, 3}, -1);
    multiplySingleThread(a, one, output, 4, 5);
    Matrix<> result({{-1, -1, -1}, {-1, 3, 3}, {6, 6, 6}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));

    multiplySingleThread(one, a, output, 4, 5);
    result = Matrix<>({{-1, -1, -1}, {-1, 3, 3}, {3, 3, 3}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, transposeWholeMatrix) {
    output = Matrix<>({3, 3}, 0);
    transposeSingleThread(c, output, 0, c.size());
    Matrix<> result({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, transposeSubMatrix) {
    output = Matrix<>({3, 3}, -1);
    transposeSingleThread(c, output, 4, 5);
    Matrix<> result({{-1, -1, -1}, {-1, 5, 8}, {3, 6, 9}});
    ASSERT_TRUE(equalSingleThread(output, result, 0, output.size()));
}

TEST_F(TestSingleThreadCalculation, symmetricWholeMatrix) {
    ASSERT_TRUE(symmetricSingleThread(sym, 0, (sym.size() - sym.rows()) / 2));
    ASSERT_FALSE(symmetricSingleThread(antisym, 0, (antisym.size() - antisym.rows()) / 2));
}

TEST_F(TestSingleThreadCalculation, symmetricSubMatrix) {
    ASSERT_TRUE(symmetricSingleThread(sym, 2, 1));
    ASSERT_FALSE(symmetricSingleThread(antisym, 2, 1));
}

TEST_F(TestSingleThreadCalculation, antisymmetricWholeMatrix) {
    ASSERT_TRUE(antisymmetricSingleThread(antisym, 0, (antisym.size() - antisym.rows()) / 2));
    ASSERT_FALSE(antisymmetricSingleThread(sym, 0, (sym.size() - sym.rows()) / 2));
}

TEST_F(TestSingleThreadCalculation, antisymmetricSubMatrix) {
    ASSERT_TRUE(antisymmetricSingleThread(antisym, 0, 2));
    ASSERT_FALSE(antisymmetricSingleThread(sym, 0, 2));
}

}  // namespace test
}  // namespace mca
