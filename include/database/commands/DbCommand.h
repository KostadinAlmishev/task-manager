//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_

#include "database/commands/IDbCommand.h"
#include "database/connection/DbConnector.h"
#include "entities/Entity.h"

template<typename Callback>
class DbCommand : public IDbCommand {
 protected:
  DbConnector<Callback> &_dbConnector;

 public:
  explicit DbCommand(DbConnector<Callback> &);
  DbCommand(const DbCommand<Callback> &) = default;

  virtual typename Callback::ResultSet *executeQuery(std::string) const;

  ~DbCommand() override = default;
};

template<typename Callback>
DbCommand<Callback>::DbCommand(DbConnector<Callback> &dbConnector)
    : _dbConnector(dbConnector) {}

template<typename Callback>
typename Callback::ResultSet *DbCommand<Callback>::executeQuery(std::string sql) const {
  auto dbConnection = _dbConnector.getConnection();
  auto connection = dbConnection->connect();
  auto result = dbConnection->execute(connection, sql);
  dbConnection->free(connection);
  _dbConnector.releaseConnection(std::move(dbConnection));
  return result;
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
