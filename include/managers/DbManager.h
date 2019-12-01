//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_

#include "database/commands/DbCommand.h"
#include "HistoryManager.h"
#include "NotificationManager.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DbManager {
 private:
  DbCommand<Connection, ResultSet> &_dbCommand;
 public:
  virtual void setCommand(const DbCommand<Connection, ResultSet> &);
  virtual void executeCommand() const;
  virtual ~DbManager() = default;
};

template<typename Connection, typename ResultSet>
void DbManager<Connection, ResultSet>::setCommand(const DbCommand<Connection, ResultSet> &dbCommand) {
  _dbCommand = dbCommand;
}

template<typename Connection, typename ResultSet>
void DbManager<Connection, ResultSet>::executeCommand() const {
  //use threads
  _dbCommand.saveBackUp();
  _dbCommand.execute();
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
