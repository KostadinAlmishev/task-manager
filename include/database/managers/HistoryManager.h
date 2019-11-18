//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_

#include "database/factories/DbCommandFactory.h"
#include "database/commands/DbCommand.h"

class HistoryManager {
 private:
  DbCommandFactory &dbCommandFactory;

 public:
  HistoryManager(DbCommandFactory &);
  virtual void push(DbCommand &) const;
  virtual DbCommand* pop() const;
  virtual ~HistoryManager() = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDHISTORY_H_
