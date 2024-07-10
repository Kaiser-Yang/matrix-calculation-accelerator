#include <example_utility.h>  // for operator<<
#include <mca/matrix.h>

#include <iostream>

int main() {
    using mca::Matrix, std::cout, mca::Shape;

    Matrix<int> m1(Shape(2, 2), 1);
    Matrix<int> m2;
    m2 = std::move(m1);
    cout << "Move assignment operator:\n";
    cout << m2;
    cout << "After move, the original matrix will be empty:\n";
    cout << m1 << "\n";

    Matrix<int> m3(Shape(2, 2), 1);
    Matrix<int> m4;
    m4 = m3;
    cout << "Copy assignment operator:\n";
    cout << m4;
    cout << "After copy, the original matrix will be the same:\n";
    cout << m3 << "\n";

    Matrix<int> m5({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    cout << m5;
    cout << "Element at index 4 (index from 0): " << m5[4] << "\n";

    return 0;
}
