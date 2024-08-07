#include <example_utility.h>  // for operator<<
#include <mca/matrix.h>
#include <mca/mca.h>

#include <iostream>

int main() {
    using mca::Matrix, mca::Shape, std::cout, std::boolalpha;

    Matrix<double> a(Shape(3, 3), 1);
    Matrix<double> b(Shape(3, 3), 2);
    double number = 2;

    cout << "Matrix a:\n";
    cout << a << "\n";

    cout << "Matrix b:\n";
    cout << b << "\n";

    cout << "Number number:\n";
    cout << number << "\n\n";

    cout << "a == b:\n";
    cout << boolalpha << (a == b) << "\n\n";

    cout << "a != b:\n";
    cout << boolalpha << (a != b) << "\n\n";

    cout << "a < b:\n";
    cout << boolalpha << (a < b) << "\n\n";

    cout << "a <= b:\n";
    cout << boolalpha << (a <= b) << "\n\n";

    cout << "a > b:\n";
    cout << boolalpha << (a > b) << "\n\n";

    cout << "a >= b:\n";
    cout << boolalpha << (a >= b) << "\n\n";

    cout << "a + b:\n";
    cout << a + b << "\n";

    cout << "a - b:\n";
    cout << a - b << "\n";

    cout << "a * b:\n";
    cout << a * b << "\n";

    cout << "a + number:\n";
    cout << a + number << "\n";

    cout << "number + a:\n";
    cout << number + a << "\n";

    cout << "a - number:\n";
    cout << a - number << "\n";

    cout << "number - a:\n";
    cout << number - a << "\n";

    cout << "a * number:\n";
    cout << a * number << "\n";

    cout << "number * a:\n";
    cout << number * a << "\n";

    cout << "a / number:\n";
    cout << a / number << "\n";

    cout << "number / a:\n";
    cout << number / a << "\n";

    Matrix<double> tmp(Shape(3, 3), 1);
    cout << "Matrix tmp :\n";
    cout << tmp << "\n";

    Matrix<double> m1 = tmp;
    cout << "m1 += tmp:\n";
    m1 += tmp;
    cout << m1 << "\n";

    Matrix<double> m2 = tmp;
    cout << "m2 -= tmp:\n";
    m2 -= tmp;
    cout << m2 << "\n";

    Matrix<double> m3 = tmp;
    cout << "m3 *= tmp:\n";
    m3 *= tmp;
    cout << m3 << "\n";

    Matrix<double> m4 = tmp;
    cout << "m4 += number:\n";
    m4 += number;
    cout << m4 << "\n";

    Matrix<double> m5 = tmp;
    cout << "number += m5:\n";
    number += m5;
    cout << m5 << "\n";

    Matrix<double> m6 = tmp;
    cout << "m6 -= number:\n";
    m6 -= number;
    cout << m6 << "\n";

    Matrix<double> m7 = tmp;
    cout << "number -= m7:\n";
    number -= m7;
    cout << m7 << "\n";

    Matrix<double> m8 = tmp;
    cout << "m8 *= number:\n";
    m8 *= number;
    cout << m8 << "\n";

    Matrix<double> m9 = tmp;
    cout << "number *= m9:\n";
    number *= m9;
    cout << m9 << "\n";

    Matrix<double> m10 = tmp;
    cout << "m10 /= number:\n";
    m10 /= number;
    cout << m10 << "\n";

    Matrix<double> m11 = tmp;
    cout << "number /= m11:\n";
    number /= m11;
    cout << m11 << "\n";

    cout << "Matrix tmp1 \n";
    Matrix<int> tmp1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << tmp1 << "\n";

    Matrix<int> m12 = tmp1;
    cout << "Transpose a matrix:\n";
    transpose(m12);
    cout << m12 << "\n";

    Matrix<int> output = tmp1;
    cout << "Transpose a matrix but store the result into matrix output:\n";
    transpose(tmp1, output);
    cout << output << "\n";

    Matrix<int> m14 = tmp1;
    cout << "Raise a matrix to the power of n:\n";
    pow(m14, number);
    cout << m14 << "\n";

    output = tmp1;
    cout << "Raise a matrix to the power of n but store the result into another matrix:\n";
    pow(tmp1, number, output);
    cout << output << "\n";

    output = tmp1;
    cout << "Calculate the numberPow of a matrix, the number set to be n:\n";
    numberPow(number, output);
    cout << output << "\n";

    output = tmp1;
    cout << "Calculate the numberPow of a matrix, the number set to be number, but store the "
            "result into another matrix:\n";
    numberPow(number, tmp1, output);
    cout << output << "\n";

    output = tmp1;
    cout << "Calculate the powNumber of a matrix, the number set to be n:\n";
    powNumber(output, number);
    cout << output << "\n";

    output = tmp1;
    cout << "Calculate the powNumber of a matrix, the number set to be number, but store the "
            "result into another matrix:\n";
    powNumber(tmp1, number, output);
    cout << output << "\n";

    return 0;
}
