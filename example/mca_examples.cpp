
#include <example_utility.h>  // for operator<<
#include <mca/matrix.h>
#include <mca/mca.h>
#include <iostream>

int main() {
    using mca::Matrix, mca::Shape, std::cout;

    Matrix<double> a(Shape(3, 3), 1);
    Matrix<double> b(Shape(3, 3), 2);
    double n = 2;

    cout << "Matrix a:\n";
    cout << a << "\n";

    cout << "Matrix b:\n";
    cout << b << "\n";

    cout << "Number n:\n";
    cout << n << "\n\n";

    cout << "a == b:\n";
    cout << (a == b) << "\n\n";

    cout << "a != b:\n";
    cout << (a != b) << "\n\n";

    cout << "a < b:\n";
    cout << (a < b) << "\n\n";

    cout << "a <= b:\n";
    cout << (a <= b) << "\n\n";

    cout << "a > b:\n";
    cout << (a > b) << "\n\n";

    cout << "a >= b:\n";
    cout << (a >= b) << "\n\n";

    cout << "a + b:\n";
    cout << a + b << "\n";
    
    cout << "a - b:\n";
    cout << a - b << "\n";

    cout << "a * b:\n";
    cout << a * b << "\n";

    cout << "a + n:\n";
    cout << a + n << "\n";

    cout << "n + a:\n";
    cout << n + a << "\n";

    cout << "a - n:\n";
    cout << a - n << "\n";

    cout << "n - a:\n";
    cout << n - a << "\n";

    cout << "a * n:\n";
    cout << a * n << "\n";

    cout << "n * a:\n";
    cout << n * a << "\n";

    cout << n / a << "\n";

    Matrix<double> m(Shape(3, 3), 1);
    cout << "Matrix m ~ m11:\n";
    cout << m << "\n";

    Matrix<double> m1(Shape(3, 3), 1);
    cout << "m1 += m:\n";
    m1 += m;
    cout << m1 << "\n";

    Matrix<double> m2(Shape(3, 3), 1);
    cout << "m2 -= m:\n";
    m2 -= m;
    cout << m2 << "\n";

    Matrix<double> m3(Shape(3, 3), 1);
    cout << "m3 *= m:\n";
    m3 *= m;
    cout << m3 << "\n";

    Matrix<double> m4(Shape(3, 3), 1);
    cout << "m4 += n:\n";
    m4 += n;
    cout << m4 << "\n";

    Matrix<double> m5(Shape(3, 3), 1);
    cout << "n += m5:\n";
    n += m5;
    cout << m5 << "\n";

    Matrix<double> m6(Shape(3, 3), 1);
    cout << "m6 -= n:\n";
    m6 -= n;
    cout << m6 << "\n";

    Matrix<double> m7(Shape(3, 3), 1);
    cout << "n -= m7:\n";
    n -= m7;
    cout << m7 << "\n";

    Matrix<double> m8(Shape(3, 3), 1);
    cout << "m8 *= n:\n";
    m8 *= n;
    cout << m8 << "\n";

    Matrix<double> m9(Shape(3, 3), 1);
    cout << "n *= m9:\n";
    n *= m9;
    cout << m9 << "\n";

    Matrix<double> m10(Shape(3, 3), 1);
    cout << "m10 /= n:\n";
    m10 /= n;
    cout << m10 << "\n";

    Matrix<double> m11(Shape(3, 3), 1);
    cout << "n /= m11:\n";
    n /= m11;
    cout << m11 << "\n";

    cout << "Matrix m12 ~ m19 \n";
    cout << Matrix<int> ({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}) << "\n";

    Matrix<int> m12({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Transpose a matrix:\n";
    transpose(m12);
    cout << m12 << "\n";
    
    Matrix<int> m13({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m13T(m13.shape(), 0);
    cout << "Transpose a matrix but store the result into another matrix:\n";
    transpose(m13, m13T);
    cout << m13T << "\n";

    Matrix<int> m14({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Raise a matrix to the power of n:\n";
    pow(m14, 2);
    cout << m14 << "\n";

    Matrix<int> m15({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m15P(m15.shape(), 0);
    cout << "Raise a matrix to the power of n but store the result into another matrix:\n";
    pow(m15, 2, m15P);
    cout << m15P << "\n";

    Matrix<int> m16({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Calculate the numberPow of a matrix, the number set to be n:\n";
    numberPow(n, m16);
    cout << m16 << "\n";

    Matrix<int> m17({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m17P(m17.shape(), 0);
    cout << "Calculate the numberPow of a matrix, the number set to be n, but store the result into another matrix:\n";
    numberPow(n, m17, m17P);
    cout << m17P << "\n";

    Matrix<int> m18({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Calculate the powNumber of a matrix, the number set to be n:\n";
    powNumber(m18, n);
    cout << m18 << "\n";

    Matrix<int> m19({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m19P(m19.shape(), 0);
    cout << "Calculate the powNumber of a matrix, the number set to be n, but store the result into another matrix:\n";
    powNumber(m19, n, m19P);
    cout << m19P << "\n";
    
    return 0;
}
