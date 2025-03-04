/**
 * @file waituntil.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief WaitUntil module.
 * @version 0.1
 * @date 2025-03-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _WAITUNTIL_HPP_
#define _WAITUNTIL_HPP_

#include <iostream>
#include <chrono>
#include <thread>

namespace Utils
{
  /**
   * @brief Namespace for handling DateTime values.
   * 
   */
  namespace DateTime
  {
    /**
     * @brief WaitUntil class.
     * @details It helps if we want to run the given operations in a certain allotted time.
     * For example: if we need to run a given SQL query every minute, the query time can vary,
     * so if we call WaitUntil in the scope at the beginning of the operation, perform the query,
     * and then wait for the remaining time with wait(), we can wait exactly 1 minute between queries.
     * 
     */
    class WaitUntil
    {
      private:
        // Variables ----
          std::chrono::milliseconds   _startTime;                                     // Time when we start.
          size_t                      _delayMilSec                = 0;                // The delay in milliseconds.

      public:
        // Construction ----
          /**
           * @brief Constructs a new WaitUntil object.
           * 
           * @param delayMilSec Delay in milliseconds.
           */
          WaitUntil(size_t delayMilSec)
            :
              _delayMilSec(delayMilSec)
          {
            // Need to set the _startTime to the time when we created WaitUntil
            _startTime = duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
          }
          /**
           * @brief Destroys the WaitUntil object.
           * 
           */
          ~WaitUntil() = default;

        // Function ----
          /**
           * @brief Waits out the remaining time.
           * 
           */
          void wait()
          {
            // Get the curretTime
            auto currentTime = duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
            // Check how much time left from the _delaySec
            std::chrono::milliseconds restMillisec((std::chrono::milliseconds(_delayMilSec)-std::chrono::milliseconds(currentTime - _startTime)));
            // If restMilliSec is more than 0 than we wait until it spends
            if(restMillisec.count() > 0) std::this_thread::sleep_for(std::chrono::milliseconds(restMillisec));
          }
          /**
           * @brief Gets the remaining milliseconds until the end of the cycle.
           * 
           * @return size_t The remaining milliseconds until the end of the cycle.
           */
          size_t remained()
          {
            // Get the curretTime
            auto currentTime = duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
            // Check how much time left from the _delaySec
            return std::chrono::milliseconds((std::chrono::milliseconds(_delayMilSec)-std::chrono::milliseconds(currentTime - _startTime))).count();
          }
    };
  }
}

#endif