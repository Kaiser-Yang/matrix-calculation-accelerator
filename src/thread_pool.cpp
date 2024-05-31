#include "mca/__mca_internal/thread_pool.h"

namespace mca {
void ThreadPool::resize(size_t newSize) {
    // if the new size is equal with the old one, do nothing
    if (newSize == size()) { return; }

    clear();
    stopped.store(false, std::memory_order_relaxed);
    assert(taskQueue.size() == 0);
    taskQueue.reserve(newSize);
    while (taskQueue.size() < newSize) {
        taskQueue.emplace_back(std::queue<std::function<void()>>());
    }
    assert(size() == 0);
    for (size_t i = 0; i < newSize; i++) {
        threadQueue.emplace([this, id = size()]() {
            std::function<void()> task;
            while (!stopped.load(std::memory_order_relaxed)) {
                if (taskQueue[id].empty()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }
                task = taskQueue[id].front();
                taskQueue[id].pop();
                task();
            }
        });
    }
}

void ThreadPool::clear() {
    stopped.store(true, std::memory_order_relaxed);
    while (!threadQueue.empty()) {
        threadQueue.front().join();
        threadQueue.pop();
    }
    std::vector<std::queue<std::function<void()>>>().swap(taskQueue);
}
}  // namespace mca
