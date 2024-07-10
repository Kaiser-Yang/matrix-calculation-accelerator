#include <example_utility.h>
#include <mca/matrix.h>

#include <iostream>

int main() {
    using mca::Matrix, mca::Shape, std::cout;

    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << m1;
    cout << "Element at (1, 1): " << m1.get(1, 1) << "\n";
    cout << "Data pointer points to the first element: " << *m1.data() << "\n";
    cout << "Rows: " << m1.rows() << "\n";
    cout << "Columns: " << m1.columns() << "\n";
    cout << "Size: " << m1.size() << "\n";
    cout << "Shape: " << m1.shape() << "\n";
    cout << "\n";

    cout << "Before reshape:\n" << m1;
    m1.reshape(Shape(1, 9));
    cout << "After reshape:\n" << m1;
    cout << "\n";

    Matrix<int> m2(Shape(3, 3));
    cout << "Before fill 5 to a matrix:\n" << m2;
    m2.fill(5);
    cout << "After fill 5 to a matrix:\n" << m2;
    cout << "\n";

    Matrix<int> m3({{1, 2}, {3, 4}});
    cout << m3;
    auto result1 = m3.numberPow(2);
    cout << "2 raised to the power of each matrix element:\n";
    cout << result1;
    auto result2 = m3.powNumber(3);
    cout << "Matrix elements raised to the power of 3:\n";
    cout << result2;
    auto result3 = m3.pow(2);
    cout << "Matrix raised to the power of 2:\n";
    cout << result3;
    cout << '\n';

    Matrix<int> m4({{1, 2, 3}, {4, 5, 6}});
    cout << "Before transpose:\n";
    cout << m4;
    auto transposed = m4.transpose();
    cout << "After transpose:\n";
    cout << transposed;
    cout << "\n";

    Matrix<int> m5({{1, 2}, {3, 4}});
    cout << m5;
    cout << "Is the matrix square? " << (m5.square() ? "Yes" : "No") << "\n";
    cout << "\n";

    Matrix<int> m6({{1, 2, 3}, {2, 5, 6}, {3, 6, 9}});
    cout << m6;
    cout << "Is the matrix symmetric? " << (m6.symmetric() ? "Yes" : "No") << "\n";
    cout << "\n";

    Matrix<int> m7({{0, 2, -3}, {-2, 0, 6}, {3, -6, 0}});
    cout << m7;
    cout << "Is the matrix antisymmetric? " << (m7.antisymmetric() ? "Yes" : "No") << "\n";
    cout << "\n";

    Matrix<int> m8({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << m8;
    cout << "First element: " << m8.front() << "\n";
    cout << "Last element: " << m8.back() << "\n";
    cout << "\n";

    Matrix<int> m9;
    cout << m9;
    cout << "Is the matrix empty? " << (m9.empty() ? "Yes" : "No") << "\n";
    cout << "\n";

    Matrix<int> m10({{1, 2}, {3, 4}});
    Matrix<int> m11({{5, 6}, {7, 8}});
    cout << "Before swap, matrix 1:\n" << m10;
    cout << "Before swap, matrix 2:\n" << m11;
    m10.swap(m11);
    cout << "After swap, matrix 1:\n" << m10;
    cout << "After swap, matrix 2:\n" << m11;

    return 0;
}
