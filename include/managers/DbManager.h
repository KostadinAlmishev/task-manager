//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_

#include "database/commands/IDbCommand.h"
#include "HistoryManager.h"
#include "NotificationManager.h"

class DbManager {
 private:
  std::shared_ptr<IDbCommand> _dbCommand;
 public:
  virtual void setCommand(std::shared_ptr<IDbCommand>);
  virtual void executeCommand() const;
  virtual ~DbManager() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
