//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_

#include "entity/Entity.h"
#include "database/connection/DbConnector.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DbCommand : public Entity {
 protected:
  DbConnector<Connection, ResultSet> &_dbConnector;

 public:
  explicit DbCommand(DbConnector<Connection, ResultSet> &);
  DbCommand(const DbCommand<Connection, ResultSet>&) = default;

  std::string toString() const override;

  virtual void saveBackUp() = 0;
  virtual void undo() const = 0;
  virtual void execute() const = 0;

  ~DbCommand() override = default;
};

template<typename Connection, typename ResultSet>
DbCommand<Connection, ResultSet>::DbCommand(DbConnector<Connection, ResultSet> &dbConnector) : _dbConnector(dbConnector) {}

template<typename Connection, typename ResultSet>
std::string DbCommand<Connection, ResultSet>::toString() const {
  return "DbCommand empty method";
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
