#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

namespace mca {
// the class is not thread-safe
// synchronizations are needed when more than one thread operate the same object of the class
class ThreadPool {
public:
    // size is the size of the thread pool
    ThreadPool(size_t size = 5) { resize(size); }

    // set a new size
    // this will not clear the taskQueue
    // if the new size is greater than the old one
    // this will not stop the previous threads
    // otherwise this will wail for all the running threads finish
    // and recreate new threads
    void resize(size_t newSize);

    // the size of the thread pool
    size_t size() { return threadQueue.size(); }

    // get the number of unstarted tasks
    // which is the size() of taskQueue
    size_t getTaskNum() {
        std::unique_lock<std::mutex> locker{mu};
        return taskQueue.size();
    }

    // add a task to the thread pool
    // this will return a std::future
    // you can use the object's get() to get the return value of your task
    template <class Function, class... Args>
    auto addTask(Function &&func, Args &&...args)
        -> std::future<std::invoke_result_t<Function, Args...>>;

    // clear the taskQueue
    // the tasks which are executing will not stop
    void clearTaskQueue() {
        std::unique_lock<std::mutex> locker{mu};
        taskQueue = std::queue<std::function<void()>>();
    }

    // clear taskQueue, and stop all threads
    // if a thread is running
    // this will wait for the thread to finish
    void clear();

    // the destructor will stop all the threads
    ~ThreadPool() { clear(); }

private:
    std::queue<std::function<void()>> taskQueue;
    std::queue<std::thread> threadQueue;
    std::mutex mu;
    std::condition_variable cv;
    volatile bool stopped;
};

template <class Function, class... Args>
auto ThreadPool::addTask(Function &&func, Args &&...args)
    -> std::future<std::invoke_result_t<Function, Args...>> {
    using ReturnType = std::invoke_result_t<Function, Args...>;
    auto taskPtr     = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Function>(func), std::forward<Args>(args)...));
    std::unique_lock<std::mutex> locker{mu};
    taskQueue.emplace([taskPtr]() { (*taskPtr)(); });
    cv.notify_one();
    return taskPtr->get_future();
}
}  // namespace mca

#endif
