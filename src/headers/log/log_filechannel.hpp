#ifndef _LOG_FILECHANNEL_HPP_
#define _LOG_FILECHANNEL_HPP_

#include <iostream>
#include <filesystem>
#include <fstream>

#include "log.hpp"
#include "../general/string.hpp"
#include "../general/datetime.hpp"

namespace drLog
{
  class FileChannel
    :
      public drLog::LogChannel
  {
    public:
      // Construction ----
        /**
         * @brief Constructs a new FileChannel object.
         * 
         * @param logPath Path of the logging files.
         * @param logLevel Level of the logging.
         * @param DTFormat DateTime format of the logging.
         */
        FileChannel(const std::string& logPath, const LogLevel& logLevel = LogLevel::LOG_LEVEL_NORMAL, const std::string& DTFormat = "%Y-%m-%d %H:%M:%S")
          :
            drLog::LogChannel(logLevel, DTFormat),
            _logPath(logPath),
            _filePath(logPath)
        {
          // Check if path is a directory and reducing it if it is
          if(!std::filesystem::is_directory(_logPath)) _filePath = _filePath.parent_path();
          // Check if the filepath exists
          if (!std::filesystem::exists(_logPath)) {
            // Trying to create the path
            if (!std::filesystem::create_directories(_logPath)) {
              std::cerr << "!!!--> Failed to create log directory structure: " << _logPath << " <--!!!\n";
              std::runtime_error("Failed to create log directory structure!");
            }
          }
        }
        /**
         * @brief Destroys the FileChannel object.
         * 
         */
        ~FileChannel() = default;

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
            // Create today's log path
            std::vector<std::string> todayDate = Utils::String::split(Utils::DateTime::getTimeTInStr(dateTime, "%Y/%m/%d"), '/');
            std::filesystem::path newFilePath = _logPath / todayDate[0] / todayDate[1] / (todayDate[2] + ".log");
            // Check the filepath
            if(_filePath!=newFilePath)
            {
              // Set the new filePath
              _filePath = newFilePath;
              // Create the new filepath
              if (!std::filesystem::exists(_filePath.parent_path())) {
                if (!std::filesystem::create_directories(_filePath.parent_path())) {
                  std::cerr << "!!!--> Failed to create today's log directory structure: " << _filePath.parent_path() << " <--!!!\n";
                  std::runtime_error("Failed to create today's log directory structure!");
                  return false;
                }
              }
              // Trying to create file (and create if it does not exists)
              std::fstream oFile(_filePath, std::ios::out | std::ios::app);
              // Check if file is okay (created)
              if(!oFile)
              {
                // Nope
                std::cerr << "!!!--> Failed to create today's log file: " << _filePath << " <--!!!\n";
                std::runtime_error("Failed to create today's log file!");
                return false;
              }
              // Close it
              oFile.close();
            }
            // Trying to open file
            std::fstream oFile(_filePath,std::ios::out | std::ios::app);
            // Check if we could open it
            if(!oFile.is_open())
            {
              // Nope
              std::cerr << "!!!--> Failed to open today's log file: " << _filePath << " <--!!!\n";
              std::runtime_error("Failed to open today's log file!");
              return false;
            }
            // At the end we will write the log
            oFile <<
              "[" << Utils::DateTime::getTimeTInStr(dateTime, p_DTFormat) + "] - " <<     // TimeStamp
              "[" << getMsgTypeStr(type) << "] " <<                                       // Type
              "<" << className << "> => " <<                                              // Sender
              message << "\n";                                                            // Message
            // Close file
            oFile.close();
          }
          return true;
        }

    private:
      // Variables ----
        std::filesystem::path       _logPath;             // Path for the log files.
        std::filesystem::path       _filePath;            // Filepath of the last log file.
  };
}

#endif