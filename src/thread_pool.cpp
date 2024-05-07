#include "thread_pool.h"

namespace mca {
void ThreadPool::resize(size_t newSize) {
    if (size() > newSize) { clear(); }
    stopped = false;
    while (threadQueue.size() < newSize) {
        threadQueue.emplace([this]() {
            std::function<void()> task;
            while (true) {
                {
                    std::unique_lock<std::mutex> locker{mu};
                    cv.wait(locker, [this]() { return stopped || !taskQueue.empty(); });
                    if (stopped) { return; }
                    task = taskQueue.front();
                    taskQueue.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::clear() {
    {
        std::unique_lock<std::mutex> locker;
        stopped   = true;
        taskQueue = std::queue<std::function<void()>>();
        cv.notify_all();
    }
    while (!threadQueue.empty()) {
        threadQueue.front().join();
        threadQueue.pop();
    }
}
}  // namespace mca
