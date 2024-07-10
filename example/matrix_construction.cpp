#include <example_utility.h>  // for operator<<
#include <mca/diag.h>
#include <mca/identity_matrix.h>
#include <mca/matrix.h>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    using mca::Matrix, mca::Shape, mca::IdentityMatrix, std::cout, std::vector, std::unique_ptr,
        std::make_unique, std::array, mca::Diag;

    Matrix<int> m1;
    cout << "Construct an empty matrix:\n";
    cout << m1 << "\n";

    Matrix<int> m2(Shape(3, 3), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (3, 3):\n";
    cout << m2 << "\n";

    Matrix<int> m3(Shape(3, 4), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (3, 4):\n";
    cout << m3 << "\n";

    Matrix<int> m4(Shape(4, 3), IdentityMatrix());
    cout << "Construct an identity matrix whose shape is (4, 3):\n";
    cout << m4 << "\n";

    Matrix<int> m5({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Construct a matrix from a std::initializer_list:\n";
    cout << m5 << "\n";

    Matrix<int> m6(vector<vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Construct a matrix from a std::vector:\n";
    cout << m6 << "\n";

    constexpr size_t len   = 6;
    unique_ptr<int[]> data = make_unique<int[]>(len);
    for (int i = 0; i < len; i++) { data[i] = i + 1; }
    Matrix<int> m7(Shape(3, 3), data.get(), len);
    cout << "Construct a matrix from a raw pointer (the last three elements will be 0):\n";
    cout << m7 << "\n";

    int arr[len] = {1, 2, 3, 4, 5, 6};
    Matrix<int> m8(Shape(3, 3), arr);
    cout << "Construct a matrix from a raw array (the last three elements will be 0):\n";
    cout << m8 << "\n";

    array<int, len> stdArr = {1, 2, 3, 4, 5, 6};
    Matrix<int> m9(Shape(3, 3), stdArr);
    cout << "Construct a matrix from a std::array (the last three elements will be 0):\n";
    cout << m9 << "\n";

    Matrix<int> m10(Shape(3, 3));
    cout << "Construct a matrix whose shape is (3, 3) and elements are all int():\n";
    cout << m10 << "\n";

    Matrix<int> m11(Shape(3, 3), -1);
    cout << "Construct a matrix whose shape is (3, 3) and elements are all -1:\n";
    cout << m11 << "\n";

    Matrix<int> m12(Diag({1, 2, 3}));
    cout << "Construct a diagonal matrix:\n";
    cout << m12 << "\n";

    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization): allow examples to copy
    Matrix<int> m13 = m12;
    cout << "Copy a matrix:\n";
    cout << m13 << "\n";

    Matrix<int> m14 = std::move(m13);
    cout << "Move a matrix:\n";
    cout << m14;
    cout << "After move, the moved matrix will be empty:\n";
    cout << m13;

    return 0;
}
