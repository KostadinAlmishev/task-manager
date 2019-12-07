//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "DbConfig.h"
#include "DbConnection.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DbConnector {
 private:
  const DbConfig &_dbConfig;
  std::mutex _mutex;
  std::condition_variable _condition;
  size_t _poolSize;
  std::queue<std::unique_ptr<DbConnection<Connection, ResultSet>>> _pool;

 public:
  explicit DbConnector(const DbConfig &);

  std::string getDbName() const;

  virtual void initializeConnectionPool(std::function<std::unique_ptr<Connection>(const DbConfig &)>,
                                        std::function<std::unique_ptr<ResultSet>(Connection &, std::string)>,
                                        std::function<void(std::unique_ptr<Connection> &&)>);
  virtual std::unique_ptr<DbConnection<Connection, ResultSet>> getConnection();
  virtual void releaseConnection(std::unique_ptr<DbConnection<Connection, ResultSet>> &&);

  DbConnector &operator=(const DbConnector &) = default;

  virtual ~DbConnector() = default;
};

template<typename Connection, typename ResultSet>
DbConnector<Connection, ResultSet>::DbConnector(const DbConfig &dbConfig)
    : _dbConfig(dbConfig), _poolSize(dbConfig.getPoolSize()) {}

template<typename Connection, typename ResultSet>
std::string DbConnector<Connection, ResultSet>::getDbName() const {
  return _dbConfig.getDbName();
}

template<typename Connection, typename ResultSet>
void DbConnector<Connection,
                 ResultSet>::initializeConnectionPool(std::function<std::unique_ptr<Connection>(const DbConfig &)> connectCallback,
                                                      std::function<std::unique_ptr<ResultSet>(Connection &,
                                                                                               std::string)> executeCallback,
                                                      std::function<void(std::unique_ptr<Connection> &&)> freeCallback) {
  std::lock_guard<std::mutex> lock(_mutex);
  if (_pool.size() == _poolSize) {
    return;
  }

  for (size_t i = 0; i < _poolSize; ++i) {
    _pool.push(std::make_unique<DbConnection<Connection, ResultSet>>(_dbConfig,
                                                                     connectCallback,
                                                                     executeCallback,
                                                                     freeCallback));
  }
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbConnection<Connection, ResultSet>> DbConnector<Connection, ResultSet>::getConnection() {
  std::unique_lock<std::mutex> lock(_mutex);

  while (_pool.empty()) {
    _condition.wait(lock);
  }

  auto dbConnection = std::move(_pool.front());
  _pool.pop();

  return dbConnection;
}

template<typename Connection, typename ResultSet>
void DbConnector<Connection, ResultSet>::releaseConnection(std::unique_ptr<DbConnection<Connection,
                                                                                        ResultSet>> &&dbConnection) {
  std::unique_lock<std::mutex> lock(_mutex);

  if (_pool.size() < _poolSize) {
    _pool.push(std::move(dbConnection));
  }

  lock.unlock();
  _condition.notify_one();
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
