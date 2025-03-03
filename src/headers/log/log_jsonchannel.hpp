#ifndef _LOG_JSONCHANNEL_HPP_
#define _LOG_JSONCHANNEL_HPP_

#include <iostream>
#include <functional>

#include "log.hpp"
#include "../general/string.hpp"
#include "../general/datetime.hpp"

#include "../vendor/nlohmann/json.hpp"

namespace drLog
{
  class JsonChannel
    :
      public drLog::LogChannel
  {
    public:
      // Construction ----
        /**
         * @brief Constructs a new JsonChannel object.
         * 
         * @param event Event callback function for the output.
         * @param logLevel Level of the logging.
         * @param DTFormat DateTime format of the logging.
         */
        JsonChannel(std::function<void(const std::string)> event, const LogLevel& logLevel = LogLevel::LOG_LEVEL_NORMAL, const std::string& DTFormat = "%Y-%m-%d %H:%M:%S")
          :
            drLog::LogChannel(logLevel, DTFormat),
            _event(event)
        {}
        /**
         * @brief Destroys the JsonChannel object.
         * 
         */
        ~JsonChannel() = default;

      // Functions ----
        /**
         * @brief Writes the log.
         * 
         * @param className Name of the sender class.
         * @param message Message we want to write
         * @param level Level of the message.
         * @param type Type of the message.
         * @param dateTime The datetime when we write it on the channel.
         * @return true Write has successed.
         * @return false Write has failed.
         */
        bool write(std::string className, std::string message, MsgLevel level, MsgType type, const std::time_t& dateTime) override
        {
          // If the message level is higher or the same we do the post
          if(int(level)>=int(p_LogLevel))
          {
            // Create json
            nlohmann::json entry;
            entry["timestamp"] = Utils::DateTime::getTimeTInStr(dateTime, p_DTFormat);
            entry["type"] = getMsgTypeStr(type);
            entry["sender"] = className;
            entry["message"] = message;
            // Write msg
            _event(entry.dump());
          }
          return true;
        }

    private:
      // Variables ----
        std::function<void(const std::string)>    _event;           // A function we use when message comes in.
  };
}

#endif