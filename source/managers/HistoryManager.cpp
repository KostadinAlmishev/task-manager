//
// Created by Konstantin Pronin on 30.11.2019.
//
#include "managers/HistoryManager.h"

#include <utility>

HistoryManager::HistoryManager(std::function<void(std::shared_ptr<Entity>)> wright_callback,
                               std::function<std::shared_ptr<Entity>()> read_callback)
    : _wrightCallback(std::move(wright_callback)), _readCallback(std::move(read_callback)) {}

void HistoryManager::push(std::shared_ptr<Entity> entity) const {
  _wrightCallback(std::move(entity));
}
std::shared_ptr<Entity> HistoryManager::pop() const {
  return _readCallback();
}



