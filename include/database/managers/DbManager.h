//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_

#include "database/commands/DbCommand.h"
#include "HistoryManager.h"
#include "tracking/Notifier.h"

class DbManager {
 private:
  DbCommand &dbCommand;
  HistoryManager &history;
  Notifier &notifier;

 public:
  DbManager(HistoryManager &, Notifier &);
  void setCommand(DbCommand &);
  void executeCommand() const;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
