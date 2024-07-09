#include <example_utility.h>  // for operator<<
#include <mca/diag.h>
#include <mca/identity_matrix.h>
#include <mca/matrix.h>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

int main() {

    using mca::Matrix;
    using std::cout;

    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Matrix elements using iterator (begin() to end()):\n";
    for (auto it = m1.begin(); it != m1.end(); ++it) {
        cout << it << " ";
    }
    cout << "\n";

    const Matrix<int> m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Matrix elements using const iterator (cbegin() to cend()):\n";
    for (auto it = m2.cbegin(); it != m2.cend(); ++it) {
        cout << it << " ";
    }
    cout << "\n";

    Matrix<int> m3({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Matrix elements using reverse iterator (rbegin() to rend()):\n";
    for (auto it = m3.rbegin(); it != m3.rend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    const Matrix<int> m4({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    cout << "Matrix elements using const reverse iterator (crbegin() to crend()):\n";
    for (auto it = m4.crbegin(); it != m4.crend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    return 0;
}
