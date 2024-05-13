#ifndef MCA_CONFIG_H
#define MCA_CONFIG_H
#include <cstddef>

#include "thread_pool.h"

namespace mca {
extern ThreadPool threadPool;
extern size_t _limit;
extern double _eps;
}  // namespace mca

#endif
