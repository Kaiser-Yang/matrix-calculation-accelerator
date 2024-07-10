#include "mca/mca.h"

#include <gtest/gtest.h>

#include <thread>

namespace mca {
namespace test {
TEST(TestConfiguration, init) {
    constexpr size_t THREAD_NUM = 10;
    init(THREAD_NUM);
    ASSERT_EQ(threadNum(), THREAD_NUM);
    ASSERT_EQ(limit(), 623);
    ASSERT_EQ(epsilon(), 1e-100);
    init(0);
}

TEST(TestConfiguration, setThreadNum) {
    setThreadNum(5);
    ASSERT_EQ(threadNum(), 5);
}

TEST(TestConfiguration, setLimit) {
    setLimit(0);
    ASSERT_EQ(limit(), 1);
}

TEST(TestConfiguration, setEpsilon) {
    setEpsilon(1e-7);
    ASSERT_EQ(epsilon(), 1e-7);
}
}  // namespace test
}  // namespace mca
