//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class AddTaskCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Task> _task;
  std::unique_ptr<Task> _backUp;

 public:
  AddTaskCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Task>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddTaskCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
AddTaskCommand<Connection, ResultSet, Callback>::AddTaskCommand(DbConnector<Connection,
                                                                            ResultSet,
                                                                            Callback> &dbConnector,
                                                                std::shared_ptr<Task> task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _task(std::move(task)) {}

template<typename Connection, typename ResultSet, typename Callback>
void AddTaskCommand<Connection, ResultSet, Callback>::saveBackUp() {
  _backUp = std::make_unique(*_task);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddTaskCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"NAME\" = \'" + _backUp->getName()
          + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddTaskCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" VALUES ("
          + _task->getName() + ","
          + _task->getDescription() + ","
          + _task->getProjectId() + ","
          + _task->getCreatorId() + ");";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_
