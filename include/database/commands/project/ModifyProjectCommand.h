//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_MODIFYPROJECTCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_MODIFYPROJECTCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

template<typename Callback>
class ModifyProjectCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _project;
  std::unique_ptr<Project> _backUp;

 public:
  ModifyProjectCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyProjectCommand() = default;
};

template<typename Callback>
ModifyProjectCommand<Callback>::ModifyProjectCommand(DbConnector<Callback> &dbConnector,
                                                     std::shared_ptr<Entity> project)
    : DbCommand<Callback>(dbConnector), _project(std::move(project)) {}

template<typename Callback>
void ModifyProjectCommand<Callback>::saveBackUp() {
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
void ModifyProjectCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _backUp->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void ModifyProjectCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_MODIFYPROJECTCOMMAND_H_
