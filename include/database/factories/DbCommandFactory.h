//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_

#include <memory>
#include <string>

#include "database/commands/DbCommand.h"
#include "entities/Entity.h"

template<typename Connection, typename ResultSet>
class DbCommandFactory {
 public:
  virtual std::unique_ptr<DbCommand<Connection, ResultSet>> createAddCommand(Entity) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet>> createDeleteCommand(Entity) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet>> createModifyCommand(Entity) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(long, long) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(std::string) const = 0;
  virtual ~DbCommandFactory() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
