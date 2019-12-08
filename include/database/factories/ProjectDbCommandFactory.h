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

template<typename Connection, typename ResultSet>
class ProjectDbCommandFactory : public DbCommandFactory<Connection, ResultSet> {
 private:
  std::function<std::unique_ptr<Project>(ResultSet)> _parseCallback;
 public:
  ProjectDbCommandFactory(DbConnector<Connection, ResultSet> &, std::function<std::unique_ptr<Project>(ResultSet)>);
  std::unique_ptr<DbCommand<Connection, ResultSet>> createAddCommand(std::shared_ptr<Project>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createDeleteCommand(std::shared_ptr<Project>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createModifyCommand(std::shared_ptr<Project>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(long, std::shared_ptr<Project>, long) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(std::string, std::shared_ptr<Project>) const override;
  ~ProjectDbCommandFactory() override = default;
};

template<typename Connection, typename ResultSet>
ProjectDbCommandFactory<Connection, ResultSet>::ProjectDbCommandFactory(DbConnector<Connection, ResultSet> &dbConnector,
                                                                  std::function<std::unique_ptr<Project>(ResultSet)> parseCallback)
    : DbCommandFactory<Connection, ResultSet>(dbConnector), _parseCallback(parseCallback) {}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> ProjectDbCommandFactory<Connection,
                                                                       ResultSet>::createAddCommand(std::shared_ptr<Project> project) const {
  return std::make_unique<AddProjectCommand<Connection, ResultSet>>(this->_dbConnector, project);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> ProjectDbCommandFactory<Connection,
                                                                       ResultSet>::createDeleteCommand(std::shared_ptr<
    Project> project) const {
  return std::make_unique<DeleteProjectCommand<Connection, ResultSet>>(this->_dbConnector, project, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> ProjectDbCommandFactory<Connection,
                                                                       ResultSet>::createModifyCommand(std::shared_ptr<
    Project> project) const {
  return std::make_unique<ModifyProjectCommand<Connection, ResultSet>>(this->_dbConnector, project, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> ProjectDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(long id,
                                                                                                    std::shared_ptr<Project> project,
                                                                                                    long) const {
  return std::make_unique<GetProjectByIdCommand<Connection, ResultSet>>(this->_dbConnector, id, project, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> ProjectDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(std::string name,
                                                                                                    std::shared_ptr<Project> project) const {
  return std::make_unique<GetProjectByIdCommand<Connection, ResultSet>>(this->_dbConnector, name, project, _parseCallback);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_PROJECTDBCOMMANDFACTORY_H_
