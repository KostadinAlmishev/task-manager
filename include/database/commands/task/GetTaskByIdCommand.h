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
template<typename Connection, typename ResultSet>
class GetTaskByIdCommand : public DbCommand<Connection, ResultSet> {
 private:
  long _id;
  std::shared_ptr<Task> _task;
  std::function<std::unique_ptr<Task>(ResultSet)> _parseCallback;

 public:
  GetTaskByIdCommand(long, std::shared_ptr<Task>, std::function<std::unique_ptr<Task>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetTaskByIdCommand() = default;
};

template<typename Connection, typename ResultSet>
GetTaskByIdCommand<Connection, ResultSet>::GetTaskByIdCommand(long id,
                                                              std::shared_ptr<Task> task,
                                                              std::function<std::unique_ptr<Task>(ResultSet)> parseCallback)
    : _id(id), _task(std::move(task)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void GetTaskByIdCommand<Connection, ResultSet>::saveBackUp() {}

template<typename Connection, typename ResultSet>
void GetTaskByIdCommand<Connection, ResultSet>::undo() const {}

template<typename Connection, typename ResultSet>
void GetTaskByIdCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where \"ID\" = \'" + _id
          + "\';";
  auto result = this->executeQuery(sql);
  *_task = *_parseCallback(result);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_
