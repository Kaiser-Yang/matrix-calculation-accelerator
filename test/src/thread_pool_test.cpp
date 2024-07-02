#include "mca/__mca_internal/thread_pool.h"

#include <gtest/gtest.h>

namespace mca {
namespace test {
TEST(TestThreadPool, defaultConstructor) {
    ThreadPool& tp = ThreadPool::getInstance();
    ASSERT_EQ(tp.size(), (size_t)0);
}

TEST(TestThreadPool, resize) {
    ThreadPool& tp = ThreadPool::getInstance(3);
    ASSERT_EQ(tp.size(), (size_t)3);
    tp.resize(5);
    ASSERT_EQ(tp.size(), (size_t)5);
    tp.resize(2);
    ASSERT_EQ(tp.size(), (size_t)2);
}

TEST(TestThreadPool, addTask) {
    ThreadPool& tp = ThreadPool::getInstance(1);
    size_t taskNum = 10;
    std::vector<std::future<size_t>> resultVector;
    for (size_t i = 0; i < taskNum; i++) {
        resultVector.emplace_back(
            tp.addTask([](size_t a, size_t b) -> size_t { return a + b; }, (size_t)2, (size_t)3));
    }
    for (size_t i = 0; i < taskNum; i++) {
        ASSERT_EQ(resultVector[i].get(), (size_t)2 + (size_t)3);
    }
}

// this test will check if the running task will be executed normally
// and if the other tasks are removed
TEST(TestThreadPool, clear) {
    using namespace std::chrono_literals;
    ThreadPool& tp = ThreadPool::getInstance(1);
    std::vector<std::future<size_t>> resultVector;
    size_t taskNum = 10;
    for (size_t i = 0; i < taskNum; i++) {
        resultVector.emplace_back(tp.addTask([]() -> size_t {
            std::this_thread::sleep_for(500ms);
            return 233;
        }));
    }
    // this is to make sure the first task is running
    std::this_thread::sleep_for(50ms);
    tp.clear();
    EXPECT_EQ(resultVector[0].get(), (size_t)233);
    ASSERT_EQ(tp.size(), size_t(0));
}

}  // namespace test
}  // namespace mca
