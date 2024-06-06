#ifndef MCA_CALCULATION_TASK_NUM
#define MCA_CALCULATION_TASK_NUM

#include <cstddef>

namespace mca {

struct CalculationTaskNum {
    using size_type = std::size_t;

    inline CalculationTaskNum() = default;
    explicit inline CalculationTaskNum(const size_type &calculation, const size_type &taskNum)
        : calculation(calculation), taskNum(taskNum) {}

    size_type calculation = 0;
    size_type taskNum     = 0;
};
}  // namespace mca

#endif
