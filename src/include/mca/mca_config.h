#ifndef MCA_MCA_CONFIG_H
#define MCA_MCA_CONFIG_H

#include "__mca_internal/thread_pool.h"

namespace mca {
using size_type = std::size_t;

/* Initialize the mca, before using mca, you must call init
 * If you don't call init, mca will run in single thread mode
 * threadNum is how many threads will be used when calculating
 * limit is the minimal quantity of a thread's calculation
 * eps is the epsilon when comparing matrices whose elements' types are floating number */
extern void init(const size_type &threadNum = std::thread::hardware_concurrency() - 1,
                 const size_type &limit     = 623,
                 const double &eps          = 1e-100);

/* Set how many threads will be used when calculating */
extern void setThreadNum(const size_type &threadNum);

/* Set the minimal quantity of a thread's calculation
 * Make sure every sub-thread's calculation is no less than limit
 * When the rest part is less than limit, the main thread will calculate the rest
 * NOTE: if you want to calculate with single thread, you can set the limit with
 *       std::numeric_limits<size_type>::max() */
extern void setLimit(const size_type &limit);

/* Set the epsilon used for comparing floating numbers */
extern void setEpsilon(const double &eps);

/* Return current thread number */
extern size_type threadNum();

/* Return current limit */
extern size_type limit();

/* Return current epsilon */
extern double epsilon();

/* Return thread pool object, this should not called by the users, and this is for developers */
extern ThreadPool &threadPool();
}  // namespace mca

#endif
