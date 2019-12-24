//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_FACTORIES_PROJECTDBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_FACTORIES_PROJECTDBCOMMANDFACTORY_H_

#include "database/commands/project/AddProjectCommand.h"
#include "database/commands/project/DeleteProjectCommand.h"
#include "database/commands/project/GetProjectByIdCommand.h"
#include "database/commands/project/GetProjectByNameCommand.h"
#include "database/commands/project/ModifyProjectCommand.h"
#include "database/factories/DbCommandFactory.h"
#include "entities/Project.h"

template<typename Callback>
class ProjectDbCommandFactory : public DbCommandFactory<Callback> {
 public:
  ProjectDbCommandFactory(DbConnector<Callback> &);
  std::unique_ptr<IDbCommand> createAddCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createDeleteCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createModifyCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createGetCommand(long,
                                               std::shared_ptr<Entity> &,
                                               long) const override;
  std::unique_ptr<IDbCommand> createGetCommand(std::string,
                                               std::shared_ptr<Entity> &) const override;
  ~ProjectDbCommandFactory() override = default;
};

template<typename Callback>
ProjectDbCommandFactory<Callback>::ProjectDbCommandFactory(DbConnector<Callback> &dbConnector)
    : DbCommandFactory<Callback>(dbConnector) {}

template<typename Callback>
std::unique_ptr<IDbCommand> ProjectDbCommandFactory<Callback>::createAddCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<AddProjectCommand<Callback>>(this->_dbConnector, project);
}

template<typename Callback>
std::unique_ptr<IDbCommand> ProjectDbCommandFactory<Callback>::createDeleteCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<DeleteProjectCommand<Callback>>(this->_dbConnector, project);
}

template<typename Callback>
std::unique_ptr<IDbCommand> ProjectDbCommandFactory<Callback>::createModifyCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<ModifyProjectCommand<Callback>>(this->_dbConnector, project);
}

template<typename Callback>
std::unique_ptr<IDbCommand> ProjectDbCommandFactory<Callback>::createGetCommand(long id,
                                                                                std::shared_ptr<
                                                                                    Entity> &project,
                                                                                long) const {
  return std::make_unique<GetProjectByIdCommand<Callback>>(this->_dbConnector, id, project);
}

template<typename Callback>
std::unique_ptr<IDbCommand> ProjectDbCommandFactory<Callback>::createGetCommand(std::string name,
                                                                                std::shared_ptr<
                                                                                    Entity> &project) const {
  return std::make_unique<GetProjectByNameCommand<Callback>>(this->_dbConnector, name, project);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_PROJECTDBCOMMANDFACTORY_H_
