/*
   _____    ____________________________ 
  /  _  \  /   _____/\_   ___ \______   \
 /  /_\  \ \_____  \ /    \  \/|     ___/
/    |    \/        \\     \___|    |    
\____|__  /_______  / \______  /____|    
        \/        \/         \/          

        Created by:ASCP11
        Util IP Library(UIL)
        @2020
*/

#include <iostream>
#include <vector>
#include <string>


class IP_util{
   public:
      bool validateIP(std::string ip){

         std::vector<std::string> slist = split(ip, '.');

         if (slist.size() != 4)
            return false;
         for (std::string str : slist){

            if (!chkNumber(str) || stoi(str) < 0 || stoi(str) > 255)
               return false;
         }
         return true;
      }
      bool ValidatePort(std::string sport){
         int port = std::stoi(sport);
         if (port > 0 and port <= 65535){
            return true;
         }
         else{
            return false;
         }
      }
   private:
      bool chkNumber(const std::string& str){
         return !str.empty() &&
         (str.find_first_not_of("[0123456789]") == std::string::npos);
      }

      std::vector<std::string> split(const std::string& str, char delim){
         auto i = 0;
         std::vector<std::string> list;
         auto pos = str.find(delim);
         while (pos != std::string::npos){
            list.push_back(str.substr(i, pos - i));
            i = ++pos;
            pos = str.find(delim, pos);
         }
         list.push_back(str.substr(i, str.length()));
         return list;
      }
};