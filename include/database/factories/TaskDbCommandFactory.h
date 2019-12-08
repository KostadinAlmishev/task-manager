//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_FACTORIES_TASKDBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_FACTORIES_TASKDBCOMMANDFACTORY_H_

#include "database/commands/task/AddTaskCommand.h"
#include "database/commands/task/DeleteTaskCommand.h"
#include "database/commands/task/GetTaskByIdCommand.h"
#include "database/commands/task/GetTaskByNameCommand.h"
#include "database/commands/task/ModifyTaskCommand.h"
#include "database/factories/DbCommandFactory.h"
#include "entities/Task.h"

template<typename Connection, typename ResultSet>
class TaskDbCommandFactory : public DbCommandFactory<Connection, ResultSet> {
 private:
  std::function<std::unique_ptr<Task>(ResultSet)> _parseCallback;
 public:
  TaskDbCommandFactory(DbConnector<Connection, ResultSet> &, std::function<std::unique_ptr<Task>(ResultSet)>);
  std::unique_ptr<DbCommand<Connection, ResultSet>> createAddCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createDeleteCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createModifyCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(long, std::shared_ptr<Task>, long) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(std::string, std::shared_ptr<Task>) const override;
  ~TaskDbCommandFactory() override = default;
};

template<typename Connection, typename ResultSet>
TaskDbCommandFactory<Connection, ResultSet>::TaskDbCommandFactory(DbConnector<Connection, ResultSet> &dbConnector,
                                                                  std::function<std::unique_ptr<Task>(ResultSet)> parseCallback)
    : DbCommandFactory<Connection, ResultSet>(dbConnector), _parseCallback(parseCallback) {}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> TaskDbCommandFactory<Connection,
                                                                       ResultSet>::createAddCommand(std::shared_ptr<Task> task) const {
  return std::make_unique<AddTaskCommand<Connection, ResultSet>>(this->_dbConnector, task);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> TaskDbCommandFactory<Connection,
                                                                       ResultSet>::createDeleteCommand(std::shared_ptr<
    Task> task) const {
  return std::make_unique<DeleteTaskCommand<Connection, ResultSet>>(this->_dbConnector, task, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> TaskDbCommandFactory<Connection,
                                                                       ResultSet>::createModifyCommand(std::shared_ptr<
    Task> task) const {
  return std::make_unique<ModifyTaskCommand<Connection, ResultSet>>(this->_dbConnector, task, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> TaskDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(long id,
                                                                                                    std::shared_ptr<Task> task,
                                                                                                    long) const {
  return std::make_unique<GetTaskByIdCommand<Connection, ResultSet>>(this->_dbConnector, id, task, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> TaskDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(std::string name,
                                                                                                    std::shared_ptr<Task> task) const {
  return std::make_unique<GetTaskByIdCommand<Connection, ResultSet>>(this->_dbConnector, name, task, _parseCallback);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_TASKDBCOMMANDFACTORY_H_
