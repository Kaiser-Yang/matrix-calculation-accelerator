#include <example_utility.h>  // for operator<<
#include <mca/identity_matrix.h>
#include <mca/matrix.h>

#include <iostream>

int main() {
    using mca::Matrix, mca::Shape, mca::IdentityMatrix, std::cout;

    Matrix<int> m1;
    cout << "Construct an empty matrix:\n";
    cout << m1 << "\n";

    Matrix<int> m2(Shape(3, 3));
    cout << "Construct a matrix whose shape is (3, 3) and elements are all int():\n";
    cout << m2 << "\n";

    Matrix<int> m3(Shape(3, 3), -1);
    cout << "Construct a matrix whose shape is (3, 3) and elements are all -1:\n";
    cout << m3 << "\n";

    Matrix<int> m4(Shape(3, 3), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (3, 3):\n";
    cout << m4 << "\n";

    Matrix<int> m5(Shape(3, 4), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (3, 4):\n";
    cout << m5 << "\n";

    Matrix<int> m6(Shape(4, 3), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (4, 3):\n";
    cout << m6 << "\n";

    return 0;
}
