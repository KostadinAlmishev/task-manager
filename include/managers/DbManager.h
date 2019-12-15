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
template<typename Connection, typename ResultSet, typename Callback>
class DbManager {
 private:
  std::shared_ptr<DbCommand<Connection, ResultSet, Callback>> _dbCommand;
 public:
  virtual void setCommand(std::shared_ptr<DbCommand<Connection, ResultSet, Callback>>);
  virtual void executeCommand() const;
  virtual ~DbManager() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
void DbManager<Connection, ResultSet, Callback>::setCommand(std::shared_ptr<DbCommand<Connection,
                                                                                      ResultSet,
                                                                                      Callback>> dbCommand) {
  _dbCommand = dbCommand;
}

template<typename Connection, typename ResultSet, typename Callback>
void DbManager<Connection, ResultSet, Callback>::executeCommand() const {
  //use threads
  _dbCommand->saveBackUp();
  _dbCommand->execute();
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBMANAGER_H_
