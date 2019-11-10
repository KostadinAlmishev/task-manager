//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_

#include <queue>

#include "DbConfig.h"
#include "DbConnection.h"

class DbConnector {
 private:
  static DbConnector *instance;
  DbConfig &dbConfig;
  std::queue<DbConnection *> pool;

 public:
  DbConnector(DbConfig &);
  virtual DbConnection *getConnection() const;
  virtual void releaseConnection() const;
  ~DbConnector();
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTOR_H_
