#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include <chrono>

#include "../headers/general/sizes.hpp"
#include "../headers/general/datetime.hpp"
#include "../headers/general/string.hpp"
#include "../headers/general/waituntil.hpp"

int main()
{
  // Wait until ----
    // Let's set the whole runtime to 5 secs
    Utils::DateTime::WaitUntil waiter(5000);
  
    // DateTime ----
      std::cout << "DateTime ----\n";
      // Get current DateTime
      time_t currentTime = Utils::DateTime::getCurrentTime();
      // Convert it to string
      std::cout << "Waiting started at: " << Utils::DateTime::getTimeTInStr(currentTime, "%d/%m/%Y %H:%M:%S") << "\n";
      // Do the same in one command
      std::cout << Utils::DateTime::getCurrentDateTimeStr() << "\n";
    
    // Sizes ----
      std::cout << "Sizes ----\n";
      // Let's take a few sizes in bytes
      size_t b1 = 87382;
      size_t b2 = 5028376;
      size_t b3 = 3076791324;
      size_t b4 = 6089311327776;
      // Print them
      std::cout << "b1 = " << Utils::sizeStr(b1) << "\n";
      std::cout << "b2 = " << Utils::sizeStr(b2) << "\n";
      std::cout << "b3 = " << Utils::sizeStr(b3) << "\n";
      std::cout << "b4 = " << Utils::sizeStr(b4) << "\n";

    // String ----
      std::cout << "String ----\n";
      // A few example
      std::string s1 = "This is an example string.";
      std::vector<std::string> sv1 = { "This", "is", "a", "chopped", "string", "." };
      // Splitting the string to pieces
      std::vector<std::string> choppedStr = Utils::String::split(s1, ' ');
      for(int i=0; i<choppedStr.size(); i++)
      {
        std::cout << "Chopped string, part " << i << ": " << choppedStr[i] << "\n";
      }
      // Now joining the pieces in sv1 from part 2 to part 4
      std::cout << Utils::String::join(sv1, " -- ", 2, 4) << "\n";
    
  // Now wait the remaining time
    // Waiting a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(2400));
    // Check how much time remained
    std::cout << "It's " << Utils::DateTime::getCurrentDateTimeStr() << "\n";
    std::cout << "Remained milliseconds from the cycle: " << waiter.remained() << "\n";
    // Wait the rest
    waiter.wait();
    std::cout << "Waiting finished at: " << Utils::DateTime::getCurrentDateTimeStr() << "\n";

  return 0;
}