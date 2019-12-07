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

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DeleteProjectCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::shared_ptr<Project> _project;
  std::unique_ptr<Project> _backUp;
  std::function<std::unique_ptr<Project>(ResultSet)> _parseCallback;

 public:
  DeleteProjectCommand(DbConnector<Connection, ResultSet> &, std::shared_ptr<Project>, std::function<std::unique_ptr<Project>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteProjectCommand() = default;
};

template<typename Connection, typename ResultSet>
DeleteProjectCommand<Connection, ResultSet>::DeleteProjectCommand(DbConnector<Connection, ResultSet> &dbConnector,
                                                            std::shared_ptr<Project> project,
                                                            std::function<std::unique_ptr<Project>(ResultSet)> parseCallback)
    : DbCommand<Connection, ResultSet>(dbConnector), _project(std::move(project)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void DeleteProjectCommand<Connection, ResultSet>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _project->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  this->_backUp = std::move(_parseCallback(result));
}

template<typename Connection, typename ResultSet>
void DeleteProjectCommand<Connection, ResultSet>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getDescription() + ");";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet>
void DeleteProjectCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _project->getName() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_DELETEPROJECTCOMMAND_H_
