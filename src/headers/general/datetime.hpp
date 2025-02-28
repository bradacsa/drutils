/**
 * @file datetime.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief DateTime functions.
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <format>

namespace Utils
{
  /**
   * @brief Namespace for handling DateTime values.
   * 
   */
  namespace DateTime
  {
    /**
     * @brief Gets the current time in time_t.
     * 
     * @return time_t The current time in time_t.
     */
    static std::time_t getCurrentTime()
    {
      return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
    /**
     * @brief Gets back a string from time_t.
     * 
     * @param dateTime DateTime we want in string.
     * @param dateTimeFormat DateTime format for the string.
     * @return std::string Time_t in DateTime string.
     */
    static std::string getTimeTInStr(const std::time_t& dateTime, const std::string& dateTimeFormat = "%Y-%m-%d %H:%M:%S")
    {
      // Convert time to local time
      tm localTime;
      localtime_r(&dateTime, &localTime);
      // Format the string
      char buffer[100];
      if (strftime(buffer, sizeof(buffer), dateTimeFormat.c_str(), &localTime)) {
        return std::string(buffer);
      }
      // On error we give back error
      return "";
    }
    /**
     * @brief Creates a datetime string with the current datetime value in the given format.
     * 
     * @param dateTimeFormat The format of the datetime.
     * @return std::string Formatted datetime string.
     */
    static std::string getCurrentDateTimeStr(const std::string& dateTimeFormat = "%Y-%m-%d %H:%M:%S")
    {
      // Get current time as a time_point
      std::time_t currentTime = getCurrentTime();
      // Calling getTimeTInStr
      return getTimeTInStr(currentTime, dateTimeFormat);
    }
  }
}

#endif