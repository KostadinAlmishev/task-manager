//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

template<typename Callback>
class GetProjectByIdCommand : public DbCommand<Callback> {
 private:
  long _id;
  std::shared_ptr<Entity> &_project;

 public:
  GetProjectByIdCommand(DbConnector<Callback> &,
                        long,
                        std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByIdCommand() = default;
};

template<typename Callback>
GetProjectByIdCommand<Callback>::GetProjectByIdCommand(DbConnector<Callback> &dbConnector,
                                                       long id,
                                                       std::shared_ptr<Entity> &project)
    : DbCommand<Callback>(dbConnector),
      _id(id),
      _project(project) {}

template<typename Callback>
void GetProjectByIdCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetProjectByIdCommand<Callback>::undo() const {}

template<typename Callback>
void GetProjectByIdCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where ID = \'" + std::to_string(_id)
          + "\';";
  auto result = this->executeQuery(sql);
  _project = std::move(Callback::parseToProject(result));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_
