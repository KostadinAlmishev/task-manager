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
template<typename Connection, typename ResultSet, typename Callback>
class DeleteProjectCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Entity> _project;
  std::unique_ptr<Project> _backUp;

 public:
  DeleteProjectCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteProjectCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
DeleteProjectCommand<Connection, ResultSet, Callback>::DeleteProjectCommand(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector,
                                                                            std::shared_ptr<Entity> project)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _project(std::move(project)) {}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteProjectCommand<Connection, ResultSet, Callback>::saveBackUp() {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToProject(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteProjectCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getDescription() + ");";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteProjectCommand<Connection, ResultSet, Callback>::execute() const {
  std::vector<Descriptor> descriptors = _project->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_DELETEPROJECTCOMMAND_H_
