/**
 * @file sizes.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief Some help in determining sizes.
 * @version 0.1
 * @date 2025-02-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _SIZES_HPP_
#define _SIZES_HPP_

#include <iostream>
#include <string>

// Sizes
#define                                 KB                                  1024ull                                     // 1 KB
#define                                 MB                                  1048576ull                                  // 1 MB
#define                                 GB                                  1073741824ull                               // 1 GB
#define                                 TB                                  1099511627776ull                            // 1 TB

namespace Utils
{
  /**
   * @brief Creates a string with the closest biggest unit.
   * 
   * @param bytes Bytes to convert.
   * @return std::string The string we get.
   */
  static std::string sizeStr(size_t bytes)
  {
    if(bytes>1*TB) { return std::to_string((double)((double)bytes/(double)TB))+" TByte(s)"; } else
    if(bytes>1*GB) { return std::to_string((double)((double)bytes/(double)GB))+" GByte(s)"; } else
    if(bytes>1*MB) { return std::to_string((double)((double)bytes/(double)MB))+" MByte(s)"; } else
    if(bytes>1*KB) { return std::to_string((double)((double)bytes/(double)KB))+" KByte(s)"; } else
    { return std::to_string((double)(bytes))+" Byte(s)"; }
  }
}

#endif