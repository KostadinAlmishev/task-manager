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

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class AddProjectCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Project> _project;
  std::unique_ptr<Project> _backUp;

 public:
  AddProjectCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Project>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddProjectCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
AddProjectCommand<Connection, ResultSet, Callback>::AddProjectCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<Project> project)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _project(std::move(project)) {}

template<typename Connection, typename ResultSet, typename Callback>
void AddProjectCommand<Connection, ResultSet, Callback>::saveBackUp() {
  _backUp = std::make_unique(*_project);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddProjectCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _backUp->getName()
          + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddProjectCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" VALUES ("
          + _project->getName() + ","
          + _project->getDescription() + ");";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_ADDPROJECTCOMMAND_H_
