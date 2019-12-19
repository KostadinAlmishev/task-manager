//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class GetTaskByIdCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  long _id;
  std::shared_ptr<Entity> &_task;

 public:
  GetTaskByIdCommand(DbConnector<Connection, ResultSet, Callback> &,
                     long,
                     std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetTaskByIdCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetTaskByIdCommand<Connection, ResultSet, Callback>::GetTaskByIdCommand(DbConnector<Connection,
                                                                                    ResultSet,
                                                                                    Callback> &dbConnector,
                                                                        long id,
                                                                        std::shared_ptr<Entity> &task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _id(id),
      _task(task) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByIdCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByIdCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByIdCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"ID\" = \'" + std::to_string(_id)
          + "\';";
  auto result = this->executeQuery(sql);
  _task = std::move(Callback::parseToTask(result));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_
