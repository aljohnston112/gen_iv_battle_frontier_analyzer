#include <future>
#include "thread_pool.h"

ThreadPool::ThreadPool(const size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(
            [this] {
                while (true) {
                    Function task;
                    {
                        std::unique_lock lock(mutex);
                        task_condition.wait(
                            lock,
                            [this] {
                                return stop || !tasks.empty();
                            }
                        );
                        if (tasks.empty() && stop) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                    {
                        std::unique_lock lock(mutex);
                        number_of_submitted_tasks.fetch_sub(
                            1,
                            std::memory_order_relaxed
                        );
                    }
                }
            }
        );
    }
}

void ThreadPool::addTask(Function&& function) {
    {
        std::lock_guard lock(mutex);
        tasks.emplace(std::move(function));
        number_of_submitted_tasks.fetch_add(
            1,
            std::memory_order_relaxed
        );
        task_condition.notify_one();
    }
}

void ThreadPool::addTasks(std::vector<Function>& functions) {
    {
        std::lock_guard lock(mutex);
        for (Function& function : functions) {
            tasks.emplace(std::move(function));
        }
        number_of_submitted_tasks.fetch_add(
            functions.size(),
            std::memory_order_relaxed
        );
        task_condition.notify_all();
    }
}

void ThreadPool::waitForTasks() {
    while (number_of_submitted_tasks.load(
            std::memory_order_relaxed
        ) > 0
    ) {
        {
            std::lock_guard lock(mutex);
            std::this_thread::yield();
        }
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard lock(mutex);
        stop = true;
        task_condition.notify_all();
    }
    for (std::jthread& thread : threads) {
        thread.join();
    }
}
