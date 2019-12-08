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
template<typename Connection, typename ResultSet>
class AddTaskCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::shared_ptr<Task> _task;
  std::unique_ptr<Task> _backUp;

 public:
  AddTaskCommand(DbConnector<Connection, ResultSet> &, std::shared_ptr<Task>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddTaskCommand() = default;
};

template<typename Connection, typename ResultSet>
AddTaskCommand<Connection, ResultSet>::AddTaskCommand(DbConnector<Connection, ResultSet> &dbConnector, std::shared_ptr<Task> task)
    : DbCommand<Connection, ResultSet>(dbConnector), _task(std::move(task)) {}

template<typename Connection, typename ResultSet>
void AddTaskCommand<Connection, ResultSet>::saveBackUp() {
  this->_backUp = std::make_unique(*_task);
}

template<typename Connection, typename ResultSet>
void AddTaskCommand<Connection, ResultSet>::undo() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"NAME\" = \'" + _backUp->getName() + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet>
void AddTaskCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" VALUES ("
          + _task->getName() + ","
          + _task->getDescription() + ","
          + _task->getProjectId() + ","
          + _task->getCreatorId() + ");";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_
