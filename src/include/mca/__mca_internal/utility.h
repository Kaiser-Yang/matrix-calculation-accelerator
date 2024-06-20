#ifndef MCA_UTILITY_H
#define MCA_UTILITY_H

#include <type_traits>

#include "calculation_task_num.h"
#include "matrix_declaration.h"
#include "mca/mca_config.h"

namespace mca {
template <class T>
struct is_matrix : std::false_type {};
template <class T>
struct is_matrix<Matrix<T>> : std::true_type {};

using size_type = std::size_t;
// Check if a type is mca::Matrix
template <class T>
inline constexpr bool is_matrix_v = is_matrix<T>::value;

/* Return calculation for every thread and the number of tasks */
inline CalculationTaskNum threadCalculationTaskNum(const size_type &total) {
    size_type calculation = std::max(total / (threadNum() + 1), limit());
    size_type taskNum     = total / calculation;
    if (total % calculation > 0) { taskNum++; }
    return CalculationTaskNum{calculation, taskNum};
}
}  // namespace mca
#endif
