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
template<typename Connection, typename ResultSet, typename Callback>
class GetProjectByIdCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  long _id;
  std::shared_ptr<Entity> &_project;

 public:
  GetProjectByIdCommand(DbConnector<Connection, ResultSet, Callback> &,
                        long,
                        std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByIdCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetProjectByIdCommand<Connection, ResultSet, Callback>::GetProjectByIdCommand(DbConnector<Connection, ResultSet, Callback> &dbConnector,
                                                                    long id,
                                                                    std::shared_ptr<Entity> &project)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _id(id),
      _project(project) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByIdCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByIdCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByIdCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where ID = \'" + std::to_string(_id)
          + "\';";
  auto result = this->executeQuery(sql);
  _project = std::move(Callback::parseToProject(result));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYIDCOMMAND_H_
