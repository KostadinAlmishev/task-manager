//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_

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
class ModifyTaskCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Task> _task;
  std::unique_ptr<Task> _backUp;

 public:
  ModifyTaskCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Task>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyTaskCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
ModifyTaskCommand<Connection, ResultSet, Callback>::ModifyTaskCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<Task> task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _task(std::move(task)) {}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"NAME\" = \'" + _task->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToTask(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set \"NAME\" = \'"
          + _backUp->getName() + "\', \"DESCRIPTION\" = \'"
          + _backUp->getDescription() + "\', \"PROJECT\" = \'"
          + _backUp->getProjectId() + "\', \"USER\" = \'"
          + _backUp->getCreatorId() + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set \"NAME\" = \'"
          + _task->getName() + "\', \"DESCRIPTION\" = \'"
          + _task->getDescription() + "\', \"PROJECT\" = \'"
          + _task->getProjectId() + "\', \"USER\" = \'"
          + _task->getCreatorId() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
