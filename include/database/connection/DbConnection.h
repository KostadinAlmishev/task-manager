//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_

#include <functional>
#include <utility>
#include <memory>

#include "database/config/DbConfig.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DbConnection {
 private:
  const DbConfig &_dbConfig;
  std::function<std::unique_ptr<Connection>(const DbConfig &)> _connectCallback;
  std::function<std::unique_ptr<ResultSet>(Connection &, std::string)> _executeCallback;
  std::function<void(std::unique_ptr<Connection>)> _freeCallback;
 public:
  DbConnection(const DbConfig &, std::function<std::unique_ptr<Connection>(const DbConfig &)>,
               std::function<std::unique_ptr<ResultSet>(Connection &, std::string)>,
               std::function<void(std::unique_ptr<Connection> &&)>);
  virtual std::unique_ptr<Connection> connect() const;
  virtual std::unique_ptr<ResultSet> execute(Connection &, const std::string &) const;
  virtual void free(std::unique_ptr<Connection> &&) const;
};

template<typename Connection, typename ResultSet>
DbConnection<Connection, ResultSet>::DbConnection(const DbConfig &dbConfig,
                                                  std::function<std::unique_ptr<Connection>(const DbConfig &)> connectCallback,
                                                  std::function<std::unique_ptr<ResultSet>(Connection &, std::string)> executeCallback,
                                                  std::function<void(std::unique_ptr<Connection> &&)> freeCallback)
    : _dbConfig(dbConfig),
      _connectCallback(std::move(connectCallback)),
      _executeCallback(std::move(executeCallback)),
      _freeCallback(std::move(freeCallback)){}

template<typename Connection, typename ResultSet>
std::unique_ptr<Connection> DbConnection<Connection, ResultSet>::connect() const {
  //use libpq
  return _connectCallback(_dbConfig);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<ResultSet> DbConnection<Connection, ResultSet>::execute(Connection &connection,
                                                                        const std::string &query) const {
  //use libpq
  return _executeCallback(connection, query);
}

template<typename Connection, typename ResultSet>
void DbConnection<Connection, ResultSet>::free(std::unique_ptr<Connection> &&connection) const {
  //use libpq
  _freeCallback(std::move(connection));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
