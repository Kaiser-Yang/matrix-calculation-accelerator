#include <algorithm>

#include "mca/__mca_internal/thread_pool.h"

namespace mca {

ThreadPool _threadPool;

size_t _limit = 623;

double _eps = 1e-100;

void init(const size_t &threadNum, const size_t &limit, const double &eps) {
    _threadPool.resize(threadNum);
    _limit = limit;
    _eps   = eps;
}

void setThreadNum(const size_t &threadNum) { _threadPool.resize(threadNum); }

void setLimit(const size_t &limit) { _limit = std::max<size_t>(1, limit); }

void setEpsilon(const double &eps) { _eps = eps; }

size_t threadNum() { return _threadPool.size(); }

size_t limit() { return _limit; }

double epsilon() { return _eps; }

ThreadPool &threadPool() { return _threadPool; }

}  // namespace mca
