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

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class ModifyProjectCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<Project> _project;
  std::unique_ptr<Project> _backUp;

 public:
  ModifyProjectCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Project>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyProjectCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
ModifyProjectCommand<Connection, ResultSet, Callback>::ModifyProjectCommand(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector,
                                                                            std::shared_ptr<Project> project)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _project(std::move(project)) {}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyProjectCommand<Connection, ResultSet,Callback>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" where \"NAME\" = \'" + _project->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToProject(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyProjectCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" set \"NAME\" = \'"
          + _backUp->getName() + "\', \"DESCRIPTION\" = \'" + _backUp->getDescription() + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyProjectCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"PROJECTS\" set \"NAME\" = \'"
          + _project->getName() + "\', \"DESCRIPTION\" = \'" + _project->getDescription() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_PROJECT_MODIFYPROJECTCOMMAND_H_
