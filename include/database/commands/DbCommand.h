//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_

#include "entity/Entity.h"
#include "database/connection/DbConnector.h"

class DbCommand {
 private:
  DbConnector dbConnector;
  Entity backUp;

 public:
  DbCommand(DbConnector *);
  void undo() const;
  Entity getBackUp() const;
  virtual void saveBackUp() = 0;
  virtual void execute() const = 0;
  virtual ~DbCommand() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
