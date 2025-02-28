/**
 * @file log.hpp
 * @author Bradács András (bradacsandras@gmail.com)
 * @brief A logging module.
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <map>

#include "../general/datetime.hpp"

/**
 * @brief drLog namespace.
 * 
 */
namespace drLog {
  // Enumerators ----
    /**
     * @brief Levels of the logging.
     * 
     */
    enum class LogLevel : unsigned int
    {
      LOG_LEVEL_DEBUG = 0,
      LOG_LEVEL_LOW = 1,
      LOG_LEVEL_NORMAL = 2,
      LOG_LEVEL_HIGH = 3,
    };
    /**
     * @brief Levels of the messages.
     * 
     */
    enum class MsgLevel : unsigned int
    {
      MSG_L_DEBUG = 0,
      MSG_L_LOW = 1,
      MSG_L_MEDIUM = 2,
      MSG_L_HIGH = 3,
    };
    /**
     * @brief Type of the messages (counted by the color of the letters in std::cout).
     * 
     */
    enum class MsgType : unsigned int
    {
      LOG_MSG = 37,
      LOG_INFO = 34,
      LOG_WARNING = 33,
      LOG_ERROR = 31,
      LOG_DEBUG = 32
    };
  
  // Functions ----
    /**
     * @brief Gives back a string name from the MsgTypes enum.
     * 
     * @param msgType The enum of the msgType.
     * @return std::string The name of the MsgType enum. 
     */
    static std::string getMsgTypeStr(const MsgType& msgType)
    {
      switch(msgType)
      {
        case MsgType::LOG_INFO:
          return "INF";
          break;
        case MsgType::LOG_WARNING:
          return "WAR";
          break;
        case MsgType::LOG_ERROR:
          return "ERR";
          break;
        case MsgType::LOG_DEBUG:
          return "DBG";
          break;
        default:
        case MsgType::LOG_MSG:
          return "MSG";
          break;
      }
    }
    /**
     * @brief Gives back a string name from the LogLevels enum.
     * 
     * @param logLevel The enum of the LogLevels.
     * @return std::string The name of the LogLevels enum.
     */
    static std::string getLogLevelStr(const LogLevel& logLevel)
    {
      switch(logLevel)
      {
        case LogLevel::LOG_LEVEL_DEBUG:
          return "DEBUG";
          break;
        case LogLevel::LOG_LEVEL_LOW:
          return "LOW";
          break;
        case LogLevel::LOG_LEVEL_HIGH:
          return "HIGH";
          break;
        default:
        case LogLevel::LOG_LEVEL_NORMAL:
          return "NORMAL";
          break;
      }
    }
  
  // Classes ----
    /**
     * @brief A generic adapter class for handling various log outputs.
     * 
     */
    class LogChannel
    {
      public:
        // Construction ----
          /**
           * @brief Constructs a new LogChannel object.
           * 
           * @param logLevel The level of the logging on the channel.
           * @param DTFormat The datetime format of the logging on the channel.
           */
          LogChannel(const LogLevel& logLevel = LogLevel::LOG_LEVEL_NORMAL, const std::string& DTFormat = "%Y-%m-%d %H:%M:%S")
            :
              p_LogLevel(logLevel),
              p_DTFormat(DTFormat)
          {}
          /**
           * @brief Destroys the Log Channel object.
           * 
           */
          virtual ~LogChannel() = default;

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
          virtual bool write(std::string className, std::string message, MsgLevel level, MsgType type, const std::time_t& dateTime) = 0;

        // Getter ----
          /**
           * @brief Gets the level of the logging of the Channel.
           * 
           * @return const LogLevels& The level of the logging of the Channel.
           */
          const LogLevel& logLevel() const
          {
            return p_LogLevel;
          }
          /**
           * @brief Gets the datetime format of the Channel.
           * 
           * @return const std::string& The datetime format of the Channel.
           */
          const std::string& DTFormat() const
          {
            return p_DTFormat;
          }

      // Setters ----
          /**
           * @brief Sets the level of the logging.
           * 
           * @param newLevel The new level of the logging.
           */
          void logLevel(LogLevel newLevel)
          {
            p_LogLevel = newLevel;
          }
          /**
           * @brief Sets the datetime format of the logging.
           * 
           * @param newDTFormat The new datetime format of the logging.
           */
          void DTFormat(const std::string& newDTFormat)
          {
            p_DTFormat = newDTFormat;
          }
      
      protected:
        // Variables ----
          LogLevel            p_LogLevel          = LogLevel::LOG_LEVEL_NORMAL;         // Level of the logging on the channel.
          std::string         p_DTFormat          = "%Y-%m-%d %H:%M:%S";                // The datetime format of the Channel.
    };
    /**
     * @brief The logging module.
     * 
     */
    class Log
    {
      public:
        // Classes ----
          /**
           * @brief An object to collect the data about what we wanted to post.
           * 
           */
          class LogPost
            :
              public std::stringstream
          {
            public:
              // Construction ----
                /**
                 * @brief Constructs a new LogPost object.
                 * 
                 * @param logger The logger parent.
                 * @param className Name of the class that sends the message.
                 * @param level Level of the message.
                 * @param type Type of the message.
                 */
                LogPost(Log& logger, const std::string& className, MsgLevel level=MsgLevel::MSG_L_LOW, MsgType type=MsgType::LOG_MSG)
                  :
                    _parentLogger(logger),
                    _className(className),
                    _level(level),
                    _type(type)
                {}
                /**
                 * @brief Destroys the LogPost object.
                 * 
                 */
                ~LogPost()
                {
                  _parentLogger._sendToChannels(_className, (*this).str(), _level, _type);
                };
              
              // Getters ----
                /**
                 * @brief Gets the message level.
                 * 
                 * @return const MsgLevels& The message level.
                 */
                const MsgLevel& msgLevel() const
                {
                  return _level;
                }
                /**
                 * @brief Gets the message type.
                 * 
                 * @return const MsgLevels& The message type.
                 */
                const MsgType& msgType() const
                {
                    return _type;
                }
                /**
                 * @brief Gets the sender's classname.
                 * 
                 * @return const MsgLevels& The sender's classname.
                 */
                const std::string& className() const
                {
                  return _className;
                }
              
            private:
              // Variables ----
                MsgLevel                _level;           // Level of the message.
                MsgType                 _type;            // Type of the message.
                const std::string       _className;       // ClassName of the message.
                Log&                    _parentLogger;    // Parent of the logpost.

          };

        // Construction ----
          /**
           * @brief Create an instance of the Log class.
           * 
           * @return Log& The instance of the log.
           */
          static Log& getInstance()
          {
            // Create instance
            static Log instance;
            // Return with the instance
            return instance;
          }
        
        // Functions ----
          /**
           * @brief Adds a channel to the channelList.
           * 
           * @param id ID of the channel.
           * @param channel The channel we want to add to the list.
           */
          void addChannel(const int& id, std::shared_ptr<LogChannel> channel)
          {
            // Check if we have channel with the same id
            if(_logChannels.contains(id))
            {
              // We have a channel with this id
              std::cerr << "!!!--> We already have a channel with ID '" << id << "' <--!!!" << std::endl;
              // Return
              return;
            }
            // Inserting channel
            _logChannels.insert( { id, channel } );
          }
          /**
           * @brief Removes a channel from the channelList.
           * 
           * @param id The channel we want to remove to the list.
           */
          void removeChannel(const int& id)
          {
            // Check if we have channel with this id
            if(!_logChannels.contains(id))
            {
                // We have a channel with this id
                std::cerr << "!!!--> We don't have a channel with ID '" << id << "' <--!!!" << std::endl;
                // Return
                return;
            }
            // Erasing this channel
            _logChannels.erase(id);
          }

        // Messages ----
          /**
           * @brief Creates a custom log post.
           * 
           * @param sender The sender of the post.
           * @param type Type of the post.
           * @param level The level of the post.
           * @return LogPost The custom LogPost.
           */  
          LogPost msg(const std::string& sender, MsgLevel level=MsgLevel::MSG_L_LOW, MsgType type=MsgType::LOG_MSG)
          {
            return LogPost(*this, sender, level, type);
          }
          /**
           * @brief Creates a 'info' log post.
           * 
           * @param sender The sender of the post.
           * @return LogPost The custom LogPost.
           */
          LogPost info(const std::string& sender)
          {
            // Call msg with the proper parameters
            return msg(sender, MsgLevel::MSG_L_MEDIUM, MsgType::LOG_INFO);
          }
          /**
           * @brief Creates a 'warning' log post.
           * 
           * @param sender The sender of the post.
           * @return LogPost The custom LogPost.
           */
          LogPost warning(const std::string& sender)
          {
            // Call msg with the proper parameters
            return msg(sender, MsgLevel::MSG_L_MEDIUM, MsgType::LOG_WARNING);
          }
          /**
           * @brief Creates a 'error' log post.
           * 
           * @param sender The sender of the post.
           * @return LogPost The custom LogPost.
           */
          LogPost error(const std::string& sender)
          {
            // Call msg with the proper parameters
            return msg(sender, MsgLevel::MSG_L_HIGH, MsgType::LOG_ERROR);
          }
          /**
           * @brief Creates a 'debug' log post.
           * 
           * @param sender The sender of the post.
           * @return LogPost The custom LogPost.
           */
          LogPost debug(const std::string& sender)
          {
            // Call msg with the proper parameters
            return msg(sender, MsgLevel::MSG_L_DEBUG, MsgType::LOG_DEBUG);
          }
      
      private:
        // Variables ----
          std::mutex                                        _writeMutex;        // A mutex for preventing writing channels simultaneously.
          std::map<int, std::shared_ptr<LogChannel>>        _logChannels;       // A container for the logging channels.

        // Construction ----
          /**
           * @brief Constructs a new Log object.
           * 
           */
          Log() = default;
          /**
           * @brief Destroys the Log object.
           * 
           */
          ~Log() = default;

        // Functions ----
          /**
           * @brief Sending message to the channels.
           * 
           * @param className Name of the sender class.
           * @param message Message we want to write
           * @param level Level of the message.
           * @param type Type of the message. 
           */
          void _sendToChannels(std::string className, std::string message, MsgLevel level, MsgType type)
          {
              // Lock the mutex
              std::lock_guard<std::mutex> lock(_writeMutex);
              // Going through channels
              for (auto& [name, channel] : _logChannels)
              {
                  // Write channel logs
                  channel->write(className, message, level, type, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
              }
          }
    
    };

  // Log Channel ----
    /**
     * @brief Standard Output Channel for the logging.
     * 
     */
    class StdOutChannel
      :
        public drLog::LogChannel
    {
      public:
        // Construction ----
          /**
           * @brief Constructs a new Standard Output Channel object.
           * 
           * @param logLevel Level of the logging.
           * @param DTFormat DateTime format of the logging.
           */
          StdOutChannel(const LogLevel& logLevel = LogLevel::LOG_LEVEL_NORMAL, const std::string& DTFormat = "%Y-%m-%d %H:%M:%S")
            :
              drLog::LogChannel(logLevel, DTFormat)
          {}
          /**
           * @brief Destroys the Standard Output Channel object.
           * 
           */
          ~StdOutChannel() = default;

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
              // Formating and write the log
              std::cout <<
                "[" << Utils::DateTime::getTimeTInStr(dateTime, p_DTFormat) << "] - " <<                    // TimeStamp
                "\033[" << std::to_string(int(type)) << "m[" + getMsgTypeStr(type) << "]\033[0m " <<        // Type
                "<" << className << "> => " <<                                                              // Sender
                message << "\n";                                                                            // Message
            }
            return true;
          }
    
    };
}

// Creates a static object from the log
static drLog::Log& drlog = drLog::Log::getInstance();

#endif
