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

template<typename Connection, typename ResultSet, typename Callback>
class ProjectDbCommandFactory : public DbCommandFactory<Connection, ResultSet, Callback> {
 public:
  ProjectDbCommandFactory(DbConnector<Connection, ResultSet, Callback> &);
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createAddCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<DbCommand<Connection,
                            ResultSet,
                            Callback>> createDeleteCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<DbCommand<Connection,
                            ResultSet,
                            Callback>> createModifyCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(long,
                                                                               std::shared_ptr<Entity> &,
                                                                               long) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> createGetCommand(std::string,
                                                                               std::shared_ptr<Entity> &) const override;
  ~ProjectDbCommandFactory() override = default;
};

template<typename Connection, typename ResultSet, typename Callback>
ProjectDbCommandFactory<Connection, ResultSet, Callback>::ProjectDbCommandFactory(DbConnector<Connection,
                                                                                              ResultSet,
                                                                                              Callback> &dbConnector)
    : DbCommandFactory<Connection, ResultSet, Callback>(dbConnector) {}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> ProjectDbCommandFactory<Connection,
                                                                                    ResultSet,
                                                                                    Callback>::createAddCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<AddProjectCommand<Connection, ResultSet, Callback>>(this->_dbConnector, project);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> ProjectDbCommandFactory<Connection,
                                                                                    ResultSet,
                                                                                    Callback>::createDeleteCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<DeleteProjectCommand<Connection, ResultSet, Callback>>(this->_dbConnector, project);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> ProjectDbCommandFactory<Connection,
                                                                                    ResultSet,
                                                                                    Callback>::createModifyCommand(std::shared_ptr<
    Entity> project) const {
  return std::make_unique<ModifyProjectCommand<Connection, ResultSet, Callback>>(this->_dbConnector, project);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> ProjectDbCommandFactory<Connection,
                                                                                    ResultSet,
                                                                                    Callback>::createGetCommand(long id,
                                                                                                                std::shared_ptr<
                                                                                                                    Entity> &project,
                                                                                                                long) const {
  return std::make_unique<GetProjectByIdCommand<Connection, ResultSet, Callback>>(this->_dbConnector, id, project);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<DbCommand<Connection, ResultSet, Callback>> ProjectDbCommandFactory<Connection,
                                                                                    ResultSet,
                                                                                    Callback>::createGetCommand(std::string name,
                                                                                                                std::shared_ptr<
                                                                                                                    Entity> &project) const {
  return std::make_unique<GetProjectByNameCommand<Connection, ResultSet, Callback>>(this->_dbConnector, name, project);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_PROJECTDBCOMMANDFACTORY_H_
