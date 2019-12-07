//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_ADDUSERCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_ADDUSERCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/User.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class AddUserCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::shared_ptr<User> _user;
  std::shared_ptr<User> _backUp;

 public:
  AddUserCommand(DbConnector<Connection, ResultSet> &, std::shared_ptr<User>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddUserCommand() = default;
};

template<typename Connection, typename ResultSet>
AddUserCommand<Connection, ResultSet>::AddUserCommand(DbConnector<Connection, ResultSet> &dbConnector, std::shared_ptr<User> user)
    : DbCommand<Connection, ResultSet>(dbConnector), _user(std::move(user)) {}

template<typename Connection, typename ResultSet>
void AddUserCommand<Connection, ResultSet>::saveBackUp() {
  this->_backUp = _user;
}

template<typename Connection, typename ResultSet>
void AddUserCommand<Connection, ResultSet>::undo() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _backUp->getName() + "\';";
  auto dbConnection = this->_dbConnector.getConnection();
  auto connection = dbConnection->connect();
  dbConnection->execute(*connection, sql);
  dbConnection->free(std::move(connection));
}

template<typename Connection, typename ResultSet>
void AddUserCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" VALUES ("
        + _user->getName() + ","
        + _user->getPassword() + ","
        + _user->getEmail() + ");";
  auto dbConnection = this->_dbConnector.getConnection();
  auto connection = dbConnection->connect();
  dbConnection->execute(*connection, sql);
  dbConnection->free(std::move(connection));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_ADDUSERCOMMAND_H_
