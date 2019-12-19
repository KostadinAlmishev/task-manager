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
template<typename Connection, typename ResultSet, typename Callback>
class GetProjectByNameCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::string _name;
  std::shared_ptr<Entity> &_project;

 public:
  GetProjectByNameCommand(DbConnector<Connection, ResultSet, Callback> &,
                          std::string,
                          std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetProjectByNameCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetProjectByNameCommand<Connection, ResultSet, Callback>::GetProjectByNameCommand(DbConnector<Connection,
                                                                                              ResultSet,
                                                                                              Callback> &dbConnector,
                                                                                  std::string name,
                                                                                  std::shared_ptr<Entity> &project)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _name(std::move(name)),
      _project(project) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByNameCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByNameCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetProjectByNameCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  _project = std::move(Callback::parseToProject(result));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_GETPROJECTBYNAMECOMMAND_H_
