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
template<typename Connection, typename ResultSet>
class ModifyTaskCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::shared_ptr<Task> _task;
  std::unique_ptr<Task> _backUp;
  std::function<std::unique_ptr<Task>(ResultSet)> _parseCallback;

 public:
  ModifyTaskCommand(DbConnector<Connection, ResultSet> &, std::shared_ptr<Task>, std::function<std::unique_ptr<Task>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyTaskCommand() = default;
};

template<typename Connection, typename ResultSet>
ModifyTaskCommand<Connection, ResultSet>::ModifyTaskCommand(DbConnector<Connection, ResultSet> &dbConnector,
                                                            std::shared_ptr<Task> task,
                                                            std::function<std::unique_ptr<Task>(ResultSet)> parseCallback)
    : DbCommand<Connection, ResultSet>(dbConnector), _task(std::move(task)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void ModifyTaskCommand<Connection, ResultSet>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"NAME\" = \'" + _task->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = _parseCallback(result);
}

template<typename Connection, typename ResultSet>
void ModifyTaskCommand<Connection, ResultSet>::undo() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set \"NAME\" = \'"
          + _backUp->getName() + "\', \"DESCRIPTION\" = \'"
          + _backUp->getDescription() + "\', \"PROJECT\" = \'"
          + _backUp->getProjectId() + "\', \"USER\" = \'"
          + _backUp->getCreatorId() + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet>
void ModifyTaskCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set \"NAME\" = \'"
          + _task->getName() + "\', \"DESCRIPTION\" = \'"
          + _task->getDescription() + "\', \"PROJECT\" = \'"
          + _task->getProjectId() + "\', \"USER\" = \'"
          + _task->getCreatorId() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
