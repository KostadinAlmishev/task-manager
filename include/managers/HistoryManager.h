//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "database/commands/IDbCommand.h"
#include "entities/User.h"

class HistoryManager {
 private:
  std::string _userName;
  std::vector<std::shared_ptr<IDbCommand>> _history;
 public:
  HistoryManager() = default;
  virtual void push(std::string, std::shared_ptr<IDbCommand>);
  virtual void pop(std::string);
  virtual ~HistoryManager() = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
