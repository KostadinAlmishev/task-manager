//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_DELETEPROJECTCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_DELETEPROJECTCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

template<typename Callback>
class DeleteProjectCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _project;
  std::unique_ptr<Project> _backUp;

 public:
  DeleteProjectCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteProjectCommand() = default;
};

template<typename Callback>
DeleteProjectCommand<Callback>::DeleteProjectCommand(DbConnector<Callback> &dbConnector,
                                                     std::shared_ptr<Entity> project)
    : DbCommand<Callback>(dbConnector),
      _project(std::move(project)) {}

template<typename Callback>
void DeleteProjectCommand<Callback>::saveBackUp() {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToProject(result));
}

template<typename Callback>
void DeleteProjectCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _backUp->createDescriptors();
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" VALUES ("
          + descriptors[1].value + ","
          + descriptors[2].value + ");";
  this->executeQuery(sql);
}

template<typename Callback>
void DeleteProjectCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_DELETEPROJECTCOMMAND_H_
