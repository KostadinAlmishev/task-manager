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

template<typename Connection, typename ResultSet, typename Callback>
class TaskDbCommandFactory : public DbCommandFactory<Connection, ResultSet, Callback> {
 public:
  TaskDbCommandFactory(DbConnector<Connection, ResultSet, Callback> &);
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createAddCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createDeleteCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createModifyCommand(std::shared_ptr<Task>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(long,
                                                                               std::shared_ptr<Task>,
                                                                               long) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(std::string,
                                                                               std::shared_ptr<Task>) const override;
  ~TaskDbCommandFactory() override = default;
};

template<typename Connection, typename ResultSet, typename Callback>
TaskDbCommandFactory<Connection, ResultSet, Callback>::TaskDbCommandFactory(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector)
    : DbCommandFactory<Connection, ResultSet, Callback>(dbConnector) {}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> TaskDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createAddCommand(
    std::shared_ptr<Task> task) const {
  return std::make_unique<AddTaskCommand<Connection, ResultSet, Callback>>(this->_dbConnector, task);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> TaskDbCommandFactory<Connection,
                                                                                 ResultSet,
                                                                                 Callback>::createDeleteCommand(std::shared_ptr<
    Task> task) const {
  return std::make_unique<DeleteTaskCommand<Connection, ResultSet, Callback>>(this->_dbConnector, task);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> TaskDbCommandFactory<Connection,
                                                                                 ResultSet,
                                                                                 Callback>::createModifyCommand(std::shared_ptr<
    Task> task) const {
  return std::make_unique<ModifyTaskCommand<Connection, ResultSet, Callback>>(this->_dbConnector, task);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> TaskDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createGetCommand(
    long id,
    std::shared_ptr<Task> task,
    long) const {
  return std::make_unique<GetTaskByIdCommand<Connection, ResultSet, Callback>>(this->_dbConnector, id, task);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> TaskDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createGetCommand(
    std::string name,
    std::shared_ptr<Task> task) const {
  return std::make_unique<GetTaskByIdCommand<Connection, ResultSet, Callback>>(this->_dbConnector, name, task);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_TASKDBCOMMANDFACTORY_H_
