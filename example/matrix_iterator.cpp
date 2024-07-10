#include <example_utility.h>  // for operator<<
#include <mca/matrix.h>

#include <iostream>

int main() {
    using mca::Matrix, std::cout;

    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    const Matrix<int> cm({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    cout << "Elements of matrix using iterator (begin() to end()):\n";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << *it << (it + 1 == m.end() ? "\n" : " ");
    }
    cout << "\n";

    cout << "Elements of const matrix using const iterator (begin() to end()):\n";
    for (auto it = cm.begin(); it != cm.end(); ++it) {
        cout << *it << (it + 1 == cm.end() ? "\n" : " ");
    }
    cout << "\n";

    cout << "Elements of matrix using reverse iterator (rbegin() to rend()):\n";
    for (auto it = m.rbegin(); it != m.rend(); ++it) {
        cout << *it << (it + 1 == m.rend() ? "\n" : " ");
    }
    cout << "\n";

    cout << "Elements of const matrix using const reverse iterator (rbegin() to rend()):\n";
    for (auto it = cm.rbegin(); it != cm.rend(); ++it) {
        cout << *it << (it + 1 == cm.rend() ? "\n" : " ");
    }

    return 0;
}
