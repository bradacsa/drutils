/**
 * @file threadpool.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief A ThreadPool implementation.
 * @version 0.1
 * @date 2025-02-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _THREADPOOL_HPP_
#define _THREADPOOL_HPP_

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

/**
 * @brief ThreadPool object implementation.
 * 
 */
class ThreadPool
{
  public:
    // Construction ----
      /**
       * @brief Constructs a new ThreadPool object.
       * 
       * @param numThreads Number of worker threads.
       */
      ThreadPool(size_t numThreads)
      {
        // Going through all the worker threads
        for (size_t i = 0; i < numThreads; ++i)
        {
          // Add a thread to the pool
          _workers.emplace_back([this]
            {
              // Run a cycle
              while (true)
              {
                // The task
                std::function<void()> task;
                {
                  // Lock the queue
                  std::unique_lock<std::mutex> lock(_queueMutex);
                  // Waiting for a task
                  _condition.wait(lock, [this] { return !_tasks.empty() || _stop; });
                  // If stop and no more tasks
                  if (_stop && _tasks.empty())
                    // Retrun
                    return;
                  // Get the task
                  task = std::move(_tasks.front());
                  _tasks.pop();
                }
                // Run the task
                task();
              }
            }
          );
        }
      }
      /**
       * @brief Destroys the ThreadPool object.
       * 
       */
      ~ThreadPool()
      {
        // Stop the queue
        {
          std::unique_lock<std::mutex> lock(_queueMutex);
          _stop = true;
        }
        // Wake up all the threads
        _condition.notify_all();
        // Join them and wait for their ends
        for (std::thread &worker : _workers)
          worker.join();
      }

    // Functions ----
      /**
       * @brief Adds new task to the queue.
       * 
       * @param task The task we want to add.
       */
      void enqueue(std::function<void()> task)
      {
        // Adds the task to the queue
        {
          std::unique_lock<std::mutex> lock(_queueMutex);
          _tasks.push(std::move(task));
        }
        // Wakes up a thread
        _condition.notify_one();
      }

  private:
    // Variables ----
      std::vector<std::thread>                        _workers;                                           // Working threads.
      std::queue<std::function<void()>>               _tasks;                                             // Tasks queue.
      std::mutex                                      _queueMutex;                                        // Lock for the queue.
      std::condition_variable                         _condition;                                         // Condition for the lock.
      bool                                            _stop                       = false;                // A stop sign for the pool.
};

#endif