#ifndef MCA_UTILITY_H
#define MCA_UTILITY_H

#include <future>
#include <type_traits>
#include <utility>
#include <vector>

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

enum class Operation : unsigned short {
    MATRIX_ADDITION,
    MATRIX_SUBTRACTION,
    MATRIX_MULTIPLICATION,

    NUMBER_MATRIX_ADDITION,
    NUMBER_MATRIX_SUBTRACTION,
    NUMBER_MATRIX_MULTIPLICATION,
    NUMBER_MATRIX_DIVISION,
    NUMBER_MATRIX_POW,

    MATRIX_NUMBER_ADDITION,
    MATRIX_NUMBER_SUBTRACTION,
    MATRIX_NUMBER_MULTIPLICATION,
    MATRIX_NUMBER_DIVISION,
    MATRIX_NUMBER_POW,

    MATRIX_EQUALITY,
    MATRIX_INEQUALITY,
    MATRIX_LESS,
    MATRIX_LESS_EQUAL,
    MATRIX_GREATER,
    MATRIX_GREATER_EQUAL,

    MATRIX_SYMMETRIC,
    MATRIX_ANTISYMMETRIC,

    MATRIX_TRANSPOSE,
    MATRIX_FILL,
    MATRIX_COPY_ASSIGNMENT,
    MATRIX_CONSTRUCT_DIAG,
    MATRIX_CONSTRUCT_FROM_POINTER,
    MATRIX_CONSTRUCT_FROM_VECTOR,
    MATRIX_CONSTRUCT_FROM_INITIALIZER_LIST,
    MATRIX_CONSTRUCT_IDENTITY,
};

template <class ReturnType, class Function>
void calculationHelper(const Operation &op,
                       const std::size_t &endPos,
                       const CalculationTaskNum &calculationTaskNum,
                       ReturnType &&returnValue,
                       Function &&function) {
    // empty matrix
    if (calculationTaskNum.taskNum == 0) {
        if constexpr (!std::is_same_v<ReturnType, std::nullptr_t>) {
            if (op == Operation::MATRIX_INEQUALITY) {
                returnValue = false;
            } else {
                returnValue = true;
            }
        }
        return;
    }
    std::vector<std::future<std::invoke_result_t<Function, const size_t &, const size_t &>>>
        subThreadReturnValue(calculationTaskNum.taskNum - 1);
    for (size_type i = 0; i < subThreadReturnValue.size(); i++) {
        subThreadReturnValue[i] =
            threadPool().addTask([start = i * calculationTaskNum.calculation,
                                  len   = calculationTaskNum.calculation,
                                  &function]() { return function(start, len); });
    }
    if constexpr (std::is_same_v<ReturnType, std::nullptr_t>) {
        function((calculationTaskNum.taskNum - 1) * calculationTaskNum.calculation,
                 endPos - (calculationTaskNum.taskNum - 1) * calculationTaskNum.calculation);
    } else {
        returnValue =
            function((calculationTaskNum.taskNum - 1) * calculationTaskNum.calculation,
                     endPos - (calculationTaskNum.taskNum - 1) * calculationTaskNum.calculation);
    }
    for (auto &item : subThreadReturnValue) {
        if constexpr (std::is_same_v<ReturnType, std::nullptr_t>) {
            item.get();
        } else {
            if (op == Operation::MATRIX_INEQUALITY) {
                returnValue |= item.get();
            } else {
                returnValue &= item.get();
            }
        }
    }
}
}  // namespace mca
#endif
