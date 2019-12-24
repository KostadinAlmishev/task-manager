//
// Created by Konstantin Pronin on 30.11.2019.
//
#include <utility>

#include "managers/HistoryManager.h"

void HistoryManager::push(std::string userName, std::shared_ptr<IDbCommand> command) {
  if (_userName != userName) {
    _userName = userName;
    _history.clear();
  }
  _history.push_back(command);
}

void HistoryManager::pop(std::string userName) {
  if (_userName == userName) {
    auto command = std::move(_history.back());
    command->undo();
  }
}
