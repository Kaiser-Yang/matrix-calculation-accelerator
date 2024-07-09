#include <example_utility.h>
#include <mca/diag.h>
#include <mca/identity_matrix.h>
#include <mca/matrix.h>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

namespace mca {
std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    os << "(" << shape.rows << ", " << shape.columns << ")";
    return os;
}
}

int main() {
    using mca::Matrix, mca::Shape, std::cout;

    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Element at (1, 1): " << m1.get(1, 1) << "\n";

    int * dataPtr = m1.data();
    cout << "Data pointer points to: " << *dataPtr << "\n";

    cout << "Rows: " << m1.rows() << "\n";

    cout << "Columns: " << m1.columns() << "\n";

    cout << "Size: " << m1.size() << "\n";

    cout << "Shape: " << m1.shape() << "\n";

    m1.reshape(Shape(1, 9));
    cout << "Reshaped matrix: " << m1 << "\n";

    Matrix<int> m2(Shape(3, 3));
    m2.fill(5);
    cout << "Matrix filled with 5:\n";
    cout << m2 << "\n";

    Matrix<int> m3({{1, 2}, {3, 4}});
    auto result1 = m3.numberPow(2);
    cout << "2 raised to the power of each matrix element:\n";
    cout << result1 << "\n";

    auto result2 = m3.powNumber(3);
    cout << "Matrix elements raised to the power of 3:\n";
    cout << result2 << "\n";

    auto result3 = m3.pow(4);
    cout << "Matrix raised to the power of 4:\n";
    cout << result3 << "\n";

    Matrix<int> m4({{1, 2, 3}, {4, 5, 6}});
    auto transposed = m4.transpose();
    cout << "Transposed matrix:\n";
    cout << transposed << "\n";

    Matrix<int> m5({{1, 2}, {3, 4}});
    cout << "Is the matrix square? " << (m5.square() ? "Yes" : "No") << "\n";

    Matrix<int> m6({{1, 2, 3}, {2, 5, 6}, {3, 6, 9}});
    cout << "Is the matrix symmetric? " << (m6.symmetric() ? "Yes" : "No") << "\n";

    Matrix<int> m7({{0, 2, -3}, {-2, 0, 6}, {3, -6, 0}});
    cout << "Is the matrix antisymmetric? " << (m7.antisymmetric() ? "Yes" : "No") << "\n";

    Matrix<int> m8({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "First element: " << m8.front() << "\n";

    cout << "Last element: " << m8.back() << "\n";

    Matrix<int> m9;
    cout << "Is the matrix empty? " << (m9.empty() ? "Yes" : "No") << "\n";

    Matrix<int> m10({{1, 2}, {3, 4}});
    Matrix<int> m11({{5, 6}, {7, 8}});
    m10.swap(m11);
    cout << "After swap, matrix 1:\n";
    cout << m10 << "\n";
    cout << "After swap, matrix 2:\n";
    cout << m11 << "\n";

    return 0;
}
