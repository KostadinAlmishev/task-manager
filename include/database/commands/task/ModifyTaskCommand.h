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
  std::shared_ptr<Entity> _task;
  std::unique_ptr<Task> _backUp;

 public:
  ModifyTaskCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyTaskCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
ModifyTaskCommand<Connection, ResultSet, Callback>::ModifyTaskCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<Entity> task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _task(std::move(task)) {}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::saveBackUp() {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToTask(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::undo() const {
  std::vector<Descriptor> descriptors = _backUp->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\', "
          + descriptors[4].field + " = \'"
          + descriptors[4].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyTaskCommand<Connection, ResultSet, Callback>::execute() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\', "
          + descriptors[4].field + " = \'"
          + descriptors[4].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
