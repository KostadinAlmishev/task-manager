//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_

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
class DeleteTaskCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Entity> _task;
  std::unique_ptr<Task> _backUp;

 public:
  DeleteTaskCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteTaskCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
DeleteTaskCommand<Connection, ResultSet, Callback>::DeleteTaskCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<Entity> task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _task(std::move(task)) {}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteTaskCommand<Connection, ResultSet, Callback>::saveBackUp() {
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
void DeleteTaskCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getDescription() + ","
          + _backUp->getProjectId() + ","
          + _backUp->getCreatorId() + ");";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteTaskCommand<Connection, ResultSet, Callback>::execute() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_
