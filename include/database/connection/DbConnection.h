//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/config/DbConfig.h"

template<typename Callback>
class DbConnection {
 private:
  const DbConfig &_dbConfig;
 public:
  explicit DbConnection(const DbConfig &);
  virtual typename Callback::Connection *connect() const;
  virtual typename Callback::ResultSet *execute(typename Callback::Connection *, const std::string &) const;
  virtual void free(typename Callback::Connection *) const;
};

template<typename Callback>
DbConnection<Callback>::DbConnection(const DbConfig &dbConfig) : _dbConfig(dbConfig) {}

template<typename Callback>
typename Callback::Connection *DbConnection<Callback>::connect() const {
  return Callback::connect(_dbConfig);
}

template<typename Callback>
typename Callback::ResultSet *DbConnection<Callback>::execute(typename Callback::Connection *connection,
                                                                  const std::string &query) const {
  return Callback::execute(connection, query);
}

template<typename Callback>
void DbConnection<Callback>::free(typename Callback::Connection *connection) const {
  Callback::free(connection);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
