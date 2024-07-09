#include <example_utility.h>  // for operator<<
#include <mca/diag.h>
#include <mca/identity_matrix.h>
#include <mca/matrix.h>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

int main() {

    using mca::Matrix, std::cout, mca::Shape;

    Matrix<int> m1(Shape(2, 2), 1);
    Matrix<int> m2;
    m2 = std::move(m1);
    cout << "Move assignment operator:\n";
    cout << m2 << "\n";
    cout << "After move, the original matrix will be empty:\n";
    cout << m1 << "\n";

    Matrix<int> m3(Shape(2, 2), 1);
    Matrix<int> m4;
    m4 = m3;
    cout << "Copy assignment operator:\n";
    cout << m4 << "\n";

    Matrix<int> m5({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Element at position 4: " << m5[4] << "\n";

    return 0;
}
