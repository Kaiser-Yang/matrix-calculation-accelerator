#ifndef MCA_UTILITY_H
#define MCA_UTILITY_H

#include <type_traits>

#include "matrix_declaration.h"

namespace mca {
template <class T>
struct is_matrix : std::false_type {};
template <class T>
struct is_matrix<Matrix<T>> : std::true_type {};

// Check if a type is mca::Matrix
template <class T>
inline constexpr bool is_matrix_v = is_matrix<T>::value;
}  // namespace mca
#endif
