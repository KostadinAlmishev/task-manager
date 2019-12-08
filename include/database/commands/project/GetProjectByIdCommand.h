//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Project.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class GetProjectByIdCommand : public DbCommand<Connection, ResultSet> {
 private:
  long _id;
  std::shared_ptr<Project> _project;
  std::function<std::unique_ptr<Project>(ResultSet)> _parseCallback;

 public:
  GetProjectByIdCommand(DbConnector<Connection, ResultSet> &,
                        long,
                        std::shared_ptr<Project>,
                        std::function<std::unique_ptr<Project>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByIdCommand() = default;
};

template<typename Connection, typename ResultSet>
GetProjectByIdCommand<Connection, ResultSet>::GetProjectByIdCommand(DbConnector<Connection, ResultSet> &dbConnector,
                                                                    long id,
                                                                    std::shared_ptr<Project> project,
                                                                    std::function<std::unique_ptr<Project>(ResultSet)> parseCallback)
    : DbCommand<Connection, ResultSet>(dbConnector),
      _id(id),
      _project(std::move(project)),
      _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void GetProjectByIdCommand<Connection, ResultSet>::saveBackUp() {}

template<typename Connection, typename ResultSet>
void GetProjectByIdCommand<Connection, ResultSet>::undo() const {}

template<typename Connection, typename ResultSet>
void GetProjectByIdCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"ID\" = \'" + _id
          + "\';";
  auto result = this->executeQuery(sql);
  *_project = *_parseCallback(result);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_
