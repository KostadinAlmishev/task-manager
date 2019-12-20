//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_

#include <utility>
#include <memory>
#include <functional>

#include "entities/Entity.h"

template <typename Callback>
class HistoryManager {
 public:
  virtual void push(std::shared_ptr<Entity>) const;
  virtual std::shared_ptr<Entity> pop() const;
  virtual ~HistoryManager() = default;
};

template <typename Callback>
void HistoryManager<Callback>::push(std::shared_ptr<Entity> entity) const {
  Callback::push(std::move(entity));
}

template <typename Callback>
std::shared_ptr<Entity> HistoryManager<Callback>::pop() const {
  return Callback::pop();
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
