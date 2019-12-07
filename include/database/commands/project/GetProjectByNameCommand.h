//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class GetProjectByNameCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::string _name;
  std::shared_ptr<Project> _project;
  std::function<std::unique_ptr<Project>(ResultSet)> _parseCallback;

 public:
  GetProjectByNameCommand(std::string, std::shared_ptr<Project>, std::function<std::shared_ptr<Project>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByNameCommand() = default;
};

template<typename Connection, typename ResultSet>
GetProjectByNameCommand<Connection, ResultSet>::GetProjectByNameCommand(std::string name,
                                                                  std::shared_ptr<Project> project,
                                                                  std::function<std::shared_ptr<Project>(ResultSet)> parseCallback)
    : _name(std::move(name)), _project(std::move(project)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void GetProjectByNameCommand<Connection, ResultSet>::saveBackUp() {}

template<typename Connection, typename ResultSet>
void GetProjectByNameCommand<Connection, ResultSet>::undo() const {}

template<typename Connection, typename ResultSet>
void GetProjectByNameCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  *_project = *_parseCallback(result);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_
