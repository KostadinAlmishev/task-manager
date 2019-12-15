//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class GetTaskByNameCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::string _name;
  std::shared_ptr<Task> _task;

 public:
  GetTaskByNameCommand(DbConnector<Connection, ResultSet, Callback> &,
                       std::string,
                       std::shared_ptr<Task>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetTaskByNameCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetTaskByNameCommand<Connection, ResultSet, Callback>::GetTaskByNameCommand(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector,
                                                                            std::string name,
                                                                            std::shared_ptr<Task> task)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _name(std::move(name)),
      _task(std::move(task)) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByNameCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByNameCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetTaskByNameCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"NAME\" = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  *_task = *Callback::parseToTask(result);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_
