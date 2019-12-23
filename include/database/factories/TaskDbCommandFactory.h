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

template<typename Callback>
class TaskDbCommandFactory : public DbCommandFactory<Callback> {
 public:
  TaskDbCommandFactory(DbConnector<Callback> &);
  std::unique_ptr<IDbCommand> createAddCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createDeleteCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createModifyCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createGetCommand(long,
                                               std::shared_ptr<Entity> &,
                                               long) const override;
  std::unique_ptr<IDbCommand> createGetCommand(std::string,
                                               std::shared_ptr<Entity> &) const override;
  ~TaskDbCommandFactory() override = default;
};

template<typename Callback>
TaskDbCommandFactory<Callback>::TaskDbCommandFactory(DbConnector<Callback> &dbConnector)
    : DbCommandFactory<Callback>(dbConnector) {}

template<typename Callback>
std::unique_ptr<IDbCommand> TaskDbCommandFactory<Callback>::createAddCommand(
    std::shared_ptr<Entity> task) const {
  return std::make_unique<AddTaskCommand<Callback>>(this->_dbConnector, task);
}

template<typename Callback>
std::unique_ptr<IDbCommand> TaskDbCommandFactory<Callback>::createDeleteCommand(std::shared_ptr<
    Entity> task) const {
  return std::make_unique<DeleteTaskCommand<Callback>>(this->_dbConnector, task);
}

template<typename Callback>
std::unique_ptr<IDbCommand> TaskDbCommandFactory<Callback>::createModifyCommand(std::shared_ptr<
    Entity> task) const {
  return std::make_unique<ModifyTaskCommand<Callback>>(this->_dbConnector, task);
}

template<typename Callback>
std::unique_ptr<IDbCommand> TaskDbCommandFactory<Callback>::createGetCommand(
    long id,
    std::shared_ptr<Entity> &task,
    long) const {
  return std::make_unique<GetTaskByIdCommand<Callback>>(this->_dbConnector, id, task);
}

template<typename Callback>
std::unique_ptr<IDbCommand> TaskDbCommandFactory<Callback>::createGetCommand(
    std::string name,
    std::shared_ptr<Entity> &task) const {
  return std::make_unique<GetTaskByNameCommand<Callback>>(this->_dbConnector, name, task);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_TASKDBCOMMANDFACTORY_H_
