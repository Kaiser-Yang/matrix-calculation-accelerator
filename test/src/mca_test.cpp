#include "mca.h"

#include <gtest/gtest.h>

#include <thread>

namespace mca {
namespace test {
TEST(TestConfiguration, init) {
    init();
    ASSERT_EQ(threadNum(), std::thread::hardware_concurrency() - 1);
    ASSERT_EQ(limit(), 623);
    ASSERT_EQ(epsilon(), 1e-100);
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

class TestMultiThreadCalculation : public testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};
// class Test
}  // namespace test
}  // namespace mca
