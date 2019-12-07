//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_

#include <utility>
#include <memory>
#include <functional>

#include "entities/Entity.h"

class HistoryManager {
 private:
  std::function<void(std::shared_ptr<Entity>)> _wrightCallback;
  std::function<std::shared_ptr<Entity>()> _readCallback;
 public:
  HistoryManager(std::function<void(std::shared_ptr<Entity>)> wright_callback,
                 std::function<std::shared_ptr<Entity>()> read_callback);
  virtual void push(std::shared_ptr<Entity>) const;
  virtual std::shared_ptr<Entity> pop() const;
  virtual ~HistoryManager() = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
