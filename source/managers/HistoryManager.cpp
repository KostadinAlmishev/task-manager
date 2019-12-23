//
// Created by Konstantin Pronin on 30.11.2019.
//
#include "managers/HistoryManager.h"

#include <utility>

void HistoryManager::push(std::string userName, std::shared_ptr<IDbCommand> command) {
  if (_userName != userName) {
    _userName = userName;
    _history.clear();
  }
  _history.push_back(command);
}

void HistoryManager::pop() {
  auto command = std::move(_history.back());
  command->undo();
}
