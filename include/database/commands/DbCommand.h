//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_

#include "entities/Entity.h"
#include "database/connection/DbConnector.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class DbCommand : public Entity {
 protected:
  DbConnector<Connection, ResultSet, Callback> &_dbConnector;

 public:
  explicit DbCommand(DbConnector<Connection, ResultSet, Callback> &);
  DbCommand(const DbCommand<Connection, ResultSet, Callback> &) = default;

  std::string toString() const override;
  virtual ResultSet executeQuery(std::string) const;

  virtual void saveBackUp() = 0;
  virtual void undo() const = 0;
  virtual void execute() const = 0;

  ~DbCommand() override = default;
};

template<typename Connection, typename ResultSet, typename Callback>
DbCommand<Connection, ResultSet, Callback>::DbCommand(DbConnector<Connection, ResultSet, Callback> &dbConnector)
    : _dbConnector(dbConnector) {}

template<typename Connection, typename ResultSet, typename Callback>
std::string DbCommand<Connection, ResultSet, Callback>::toString() const {
  return "DbCommand empty method";
}

template<typename Connection, typename ResultSet, typename Callback>
ResultSet DbCommand<Connection, ResultSet, Callback>::executeQuery(std::string sql) const {
  auto dbConnection = _dbConnector.getConnection();
  auto connection = dbConnection->connect();
  auto result = dbConnection->execute(*connection, sql);
  dbConnection->free(std::move(connection));
  return result;
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
