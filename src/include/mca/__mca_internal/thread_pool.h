#ifndef MCA_THREAD_POOL_H
#define MCA_THREAD_POOL_H

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

namespace mca {
/* the class is not thread-safe
 * synchronizations are needed when more than one thread operate the same object of the class */
class ThreadPool {
public:
    using size_type = std::size_t;

    /* get the instance of the thread pool */
    inline static ThreadPool &getInstance(size_type size = 0) {
        static ThreadPool instance;
        instance.resize(size);
        return instance;
    }

    /* the copy constructor and assignment operator are deleted
     * to avoid multiple instances of the thread pool */
    ThreadPool(const ThreadPool &)             = delete;
    ThreadPool(const ThreadPool &&)            = delete;
    ThreadPool &operator=(const ThreadPool &)  = delete;
    ThreadPool &operator=(const ThreadPool &&) = delete;

    /* set a new size, and this will clear the task queue
     * this will wait for all the running threads finish their current tasks, then stop them
     * and create new threads */
    void resize(size_type newSize);

    /* the size of the thread pool */
    inline size_type size() { return threadQueue.size(); }

    /* add a task to the thread pool
     * this will return a std::future
     * you can use the object's get() to get the return value of your task
     * NOTE: you can not add a task to a thread pool whose size is 0 */
    template <class Function, class... Args>
    auto addTask(Function &&func, Args &&...args)
        -> std::future<std::invoke_result_t<Function, Args...>>;

    /* stop all threads and clear the task queue
     * if a thread is running
     * this will wait for the thread to finish */
    void clear();

    /* the destructor will stop all the threads */
    inline ~ThreadPool() { clear(); }

private:
    inline ThreadPool() = default;
    /* private constructor, use getInstance() to get the instance */
    std::vector<std::queue<std::function<void()>>> taskQueue;
    std::queue<std::thread> threadQueue;
    size_type i{0};
    std::atomic<bool> stopped{false};
};

template <class Function, class... Args>
auto ThreadPool::addTask(Function &&func, Args &&...args)
    -> std::future<std::invoke_result_t<Function, Args...>> {
    assert(size() != 0);
    using ReturnType = std::invoke_result_t<Function, Args...>;
    auto taskPtr     = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Function>(func), std::forward<Args>(args)...));
    taskQueue[i].emplace([taskPtr]() { (*taskPtr)(); });
    i = (i + 1) % size();
    return taskPtr->get_future();
}
}  // namespace mca

#endif
