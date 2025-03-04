/**
 * @file string.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief String functions.
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace Utils
{
  /**
   * @brief Namespace for some string handling.
   * 
   */
  namespace String
  {
    /**
     * @brief Splits strings into pieces.
     * 
     * @param text The text we want to split.
     * @param delimiter The delimiter we want to use to split.
     * @param emptyAtFail Should we return empty if we can't find any delimiter.
     * @return std::vector<std::string> The splitted strings in vector.
     */
    static std::vector<std::string> split(const std::string& text, char delimiter, bool emptyAtFail = true)
    {
      // Create return vector
      std::vector<std::string> result;
      // Create string_view
      std::string_view view(text);
      // Start position
      std::size_t start = 0;
      // Current position
      std::size_t pos;
      // Going through the view
      while ((pos = view.find(delimiter, start)) != std::string_view::npos)
      {
        // Add part to the result
        result.emplace_back(view.substr(start, pos - start));
        // Step after the delimeter
        start = pos + 1;
      }
      // Add last part (after the last separator)
      if (start < view.size() && start != 0)
      {
        result.emplace_back(view.substr(start));
      }
      // Check if we should return empty if we can't find any delimiter
      if (result.empty() && !emptyAtFail)
      {
        result.emplace_back(text);
      }
      // Return with the string vector
      return result;
    }
    /**
     * @brief Joins strings with a delimiter.
     * 
     * @param strings The list of the strings we want to join.
     * @param delimiter The delimiter we want to use between the strings.
     * @param from It will starts from this element of the list.
     * @param to It will ends at this element of the list. -1 means to the end of the list.
     * @return std::string The joined string.
     */
    static std::string join(const std::vector<std::string> &strings, const std::string &delimiter = "", int from = 0, int to = -1)
    {
      // If to is -1 then we use the length of the string
      if(to == -1)
      {
        to = strings.size();
      }
      // If the string is empty we return empty string
      if (strings.empty()) {
        return "";
      }
      // Put the first string into the result
      std::string result = strings[from];
      // Put the others into the result string
      for (std::size_t i = from + 1; i <= to; ++i) {
        result += delimiter + strings[i];
      }
      // Return with the result
      return result;
    }
  }
}

#endif