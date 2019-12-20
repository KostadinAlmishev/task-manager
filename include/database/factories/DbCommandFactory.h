//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_

#include <memory>
#include <string>

#include "database/commands/DbCommand.h"
#include "entities/Entity.h"

template<typename Connection, typename ResultSet, typename Callback>
class DbCommandFactory {
 protected:
  DbConnector<Connection, ResultSet, Callback> &_dbConnector;
 public:
  explicit DbCommandFactory(DbConnector<Connection, ResultSet, Callback> &dbConnector) : _dbConnector(dbConnector) {}
  virtual std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createAddCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createDeleteCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createModifyCommand(std::shared_ptr<Entity>) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(long, std::shared_ptr<Entity> &, long) const = 0;
  virtual std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(std::string, std::shared_ptr<Entity> &) const = 0;
  virtual ~DbCommandFactory() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMANDFACTORY_H_
