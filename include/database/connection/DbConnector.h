//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "database/config/DbConfig.h"
#include "DbConnection.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class DbConnector {
 private:
  const DbConfig &_dbConfig;
  std::mutex _mutex;
  std::condition_variable _condition;
  size_t _poolSize;
  std::queue<std::unique_ptr<DbConnection<Connection, ResultSet, Callback>>> _pool;

 public:
  explicit DbConnector(const DbConfig &);

  std::string getDbName() const;

  virtual void initializeConnectionPool();
  virtual std::unique_ptr<DbConnection<Connection, ResultSet, Callback>> getConnection();
  virtual void releaseConnection(std::unique_ptr<DbConnection<Connection, ResultSet, Callback>> &&);

  DbConnector &operator=(const DbConnector &) = default;

  virtual ~DbConnector() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
DbConnector<Connection, ResultSet, Callback>::DbConnector(const DbConfig &dbConfig)
    : _dbConfig(dbConfig), _poolSize(dbConfig.getPoolSize()) {}

template<typename Connection, typename ResultSet, typename Callback>
std::string DbConnector<Connection, ResultSet, Callback>::getDbName() const {
  return _dbConfig.getDbName();
}

template<typename Connection, typename ResultSet, typename Callback>
void DbConnector<Connection, ResultSet, Callback>::initializeConnectionPool() {
  std::lock_guard<std::mutex> lock(_mutex);
  if (_pool.size() == _poolSize) {
    return;
  }

  for (size_t i = 0; i < _poolSize; ++i) {
    _pool.push(std::make_unique<DbConnection<Connection, ResultSet, Callback>>(_dbConfig));
  }
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbConnection<Connection, ResultSet, Callback>> DbConnector<Connection,
                                                                           ResultSet,
                                                                           Callback>::getConnection() {
  std::unique_lock<std::mutex> lock(_mutex);

  while (_pool.empty()) {
    _condition.wait(lock);
  }

  auto dbConnection = std::move(_pool.front());
  _pool.pop();

  return dbConnection;
}

template<typename Connection, typename ResultSet, typename Callback>
void DbConnector<Connection, ResultSet, Callback>::releaseConnection(std::unique_ptr<DbConnection<Connection,
                                                                                                  ResultSet,
                                                                                                  Callback>> &&dbConnection) {
  std::unique_lock<std::mutex> lock(_mutex);

  if (_pool.size() < _poolSize) {
    _pool.push(std::move(dbConnection));
  }

  lock.unlock();
  _condition.notify_one();
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
