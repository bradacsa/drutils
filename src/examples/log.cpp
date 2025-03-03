/**
 * @file log.cpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief Example for using Log object.
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>

#include "../headers/log/log.hpp"
#include "../headers/log/log_filechannel.hpp"
#include "../headers/log/log_jsonchannel.hpp"

int main()
{
  /*
    Logging levels:
      - debug:    MSG, INF, WAR, ERR, DBG
      - low:      MSG, INF, WAR, ERR
      - normal:   INF, WAR, ERR
      - high:     ERR
  */
 
  // Add some channels to the log
    // StdOutChannel - Writing on the screen -> Normal level = MSG and DBG are hidden
    drlog.addChannel(0, std::make_shared<drLog::StdOutChannel>(drLog::LogLevel::LOG_LEVEL_NORMAL));
    // FileChannel - Writing into files -> Debug level = everything is visible
    drlog.addChannel(1, std::make_shared<drLog::FileChannel>("logs/", drLog::LogLevel::LOG_LEVEL_DEBUG));
    // JsonChannel - Puts a json string trough a callback function -> High level = only see the errors
    drlog.addChannel(2, std::make_shared<drLog::JsonChannel>([](std::string json){ std::cout << json << "\n"; }, drLog::LogLevel::LOG_LEVEL_HIGH));

  // Log something
  drlog.msg("main") << "This is a normal message.";
  drlog.info("main") << "This is an info message.";
  drlog.warning("main") << "This is a warning message.";
  drlog.error("main") << "This is an error message.";
  drlog.debug("main") << "This is a debug message.";
  // Returning
  return 0;
}