//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_

#include <memory>
#include <string>

#include "database/commands/DbCommand.h"
#include "database/commands/IDbCommand.h"
#include "entities/Entity.h"

template<typename Connection, typename ResultSet, typename Callback>
class DbCommandFactory {
 protected:
  DbConnector<Connection, ResultSet, Callback> &_dbConnector;
 public:
  explicit DbCommandFactory(DbConnector<Connection, ResultSet, Callback> &dbConnector) : _dbConnector(dbConnector) {}
  virtual std::unique_ptr<IDbCommand> createAddCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<IDbCommand> createDeleteCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<IDbCommand> createModifyCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<IDbCommand> createGetCommand(long, std::shared_ptr<Entity> &, long) const = 0;
  virtual std::unique_ptr<IDbCommand> createGetCommand(std::string, std::shared_ptr<Entity> &) const = 0;
  virtual ~DbCommandFactory() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
