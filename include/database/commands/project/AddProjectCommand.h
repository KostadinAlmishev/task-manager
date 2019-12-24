//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_ADDPROJECTCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_ADDPROJECTCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

template<typename Callback>
class AddProjectCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _project;

 public:
  AddProjectCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddProjectCommand() = default;
};

template<typename Callback>
AddProjectCommand<Callback>::AddProjectCommand(DbConnector<Callback> &dbConnector,
                                               std::shared_ptr<Entity> project)
    : DbCommand<Callback>(dbConnector), _project(std::move(project)) {}

template<typename Callback>
void AddProjectCommand<Callback>::saveBackUp() {}

template<typename Callback>
void AddProjectCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void AddProjectCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" ("
          + descriptors[1].field + ", "
          + descriptors[2].field + ") VALUES (\'"
          + descriptors[1].value + "\',\'"
          + descriptors[2].value + "\');";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_ADDPROJECTCOMMAND_H_
