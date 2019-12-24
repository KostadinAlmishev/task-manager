//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

template<typename Callback>
class GetProjectByNameCommand : public DbCommand<Callback> {
 private:
  std::string _name;
  std::shared_ptr<Entity> &_project;

 public:
  GetProjectByNameCommand(DbConnector<Callback> &,
                          std::string,
                          std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByNameCommand() = default;
};

template<typename Callback>
GetProjectByNameCommand<Callback>::GetProjectByNameCommand(DbConnector<Callback> &dbConnector,
                                                           std::string name,
                                                           std::shared_ptr<Entity> &project)
    : DbCommand<Callback>(dbConnector),
      _name(std::move(name)),
      _project(project) {}

template<typename Callback>
void GetProjectByNameCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetProjectByNameCommand<Callback>::undo() const {}

template<typename Callback>
void GetProjectByNameCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where NAME = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  _project = std::move(Callback::parseToProject(result));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_
