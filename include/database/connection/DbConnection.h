//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/config/DbConfig.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class DbConnection {
 private:
  const DbConfig &_dbConfig;
 public:
  explicit DbConnection(const DbConfig &);
  virtual Connection *connect() const;
  virtual ResultSet *execute(Connection *, const std::string &) const;
  virtual void free(Connection *) const;
};

template<typename Connection, typename ResultSet, typename Callback>
DbConnection<Connection, ResultSet, Callback>::DbConnection(const DbConfig &dbConfig) : _dbConfig(dbConfig) {}

template<typename Connection, typename ResultSet, typename Callback>
Connection *DbConnection<Connection, ResultSet, Callback>::connect() const {
  return Callback::connect(_dbConfig);
}

template<typename Connection, typename ResultSet, typename Callback>
ResultSet *DbConnection<Connection, ResultSet, Callback>::execute(Connection *connection,
                                                                  const std::string &query) const {
  return Callback::execute(connection, query);
}

template<typename Connection, typename ResultSet, typename Callback>
void DbConnection<Connection, ResultSet, Callback>::free(Connection *connection) const {
  Callback::free(connection);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
