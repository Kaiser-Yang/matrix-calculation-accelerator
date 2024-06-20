#ifndef MCA_EXAMPLE_UTILITY
#define MCA_EXAMPLE_UTILITY

#include <mca/matrix.h>

#include <iostream>

template <class T>
std::ostream &operator<<(std::ostream &os, mca::Matrix<T> m) {
    std::cout << "Shape(rows, columns): (" << m.rows() << ", " << m.columns() << ")\n";
    std::cout << "Elements:\n";
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.columns(); j++) {
            std::cout << std::left << m.get(i, j) << (j == m.columns() - 1 ? "\n" : " ");
        }
    }
    return os;
}

#endif
