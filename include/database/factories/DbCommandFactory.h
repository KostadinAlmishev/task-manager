//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_

#include <string>

#include "database/commands/DbCommand.h"
#include "entity/Entity.h"

class DbCommandFactory {
 public:
  virtual DbCommand *createAddCommand(Entity) const = 0;
  virtual DbCommand *createDeleteCommand(Entity) const = 0;
  virtual DbCommand *createModifyCommand(Entity) const = 0;
  virtual DbCommand *createGetCommand(long, long) const = 0;
  virtual DbCommand *createGetCommand(std::string) const = 0;
  virtual ~DbCommandFactory() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
