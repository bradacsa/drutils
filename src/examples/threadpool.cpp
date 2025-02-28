/**
 * @file threadpool.cpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief Example for using ThreadPool object.
 * @version 0.1
 * @date 2025-02-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <functional>
#include <mutex>

#include "../headers/general/threadpool.hpp"

int main()
{
  // Declaring a ThreadPool
  ThreadPool threadpool(10);
  // Declaring a mutex to preventing write cout randomly
  std::mutex writeMutex;

  // Creating 10 threads
  for(int i=0; i<10; i++)
  {
    // Get a thread
    threadpool.enqueue( [i, &writeMutex]()
      {
        // Counting 0 to 9
        for(int j=0; j<10; j++)
        {
          // Lock the mutex
          std::lock_guard<std::mutex> lock(writeMutex);
          // Write the line
          std::cout << i << " -> " << j << "\n";
        }
      }
    );
  }
  // Returning
  return 0;
}