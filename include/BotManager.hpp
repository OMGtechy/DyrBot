#ifndef BOT_MANAGER_HPP
#define BOT_MANAGER_HPP

#include <queue>
#include <mutex>
#include <map>

#include <boost/thread.hpp>

#include "DyrBot.hpp"
#include "DyrBotErrors.hpp"

namespace dyr
{
  class BotManager
  {
    public:
      BotManager(){}
      //BotManager(const std::string& default_config);
      ~BotManager();

      int getBotCount();

      int createBot();
      bool deleteBot(int id);
      bool exist(int id);

      void connectBots();
      void process_loop();

      void notify_ready(const int& id);

      void append_error(const int& id, DyrError&& error);
      void process_error();

    private:
      boost::mutex mtx;

      std::map<int, DyrBot> id_bot_map;
      std::map<int, boost::thread> id_bot_thread;

      std::queue<std::pair<int, DyrError> > bot_errors;

      int generateID();

      BotManager(const BotManager&) = delete; //Copy Constructor
      BotManager(BotManager&& other) noexcept = delete; //Move Constructor
      BotManager& operator=(const BotManager& other) = delete; //Copy Assignment
      BotManager& operator=(BotManager&& other) noexcept = delete; //Move Assignment

  };
}

#endif /*BOT_MANAGER_HPP*/
