//
// Created by Konstantin Pronin on 29.11.2019.
//

#include "managers/DbManager.h"

void DbManager::setCommand(std::shared_ptr<IDbCommand> dbCommand) {
  _dbCommand = dbCommand;
}

void DbManager::executeCommand() const {
  //use threads
  _dbCommand->saveBackUp();
  _dbCommand->execute();
}