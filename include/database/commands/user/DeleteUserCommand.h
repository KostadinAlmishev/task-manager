//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEUSERCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEUSERCOMMAND_H_

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
class DeleteUserCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::shared_ptr<User> _user;
  std::unique_ptr<User> _backUp;
  std::function<std::unique_ptr<User>(ResultSet)> _parseCallback;

 public:
  DeleteUserCommand(DbConnector<Connection, ResultSet> &, std::shared_ptr<User>, std::function<std::unique_ptr<User>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteUserCommand() = default;
};

template<typename Connection, typename ResultSet>
DeleteUserCommand<Connection, ResultSet>::DeleteUserCommand(DbConnector<Connection, ResultSet> &dbConnector,
                                                            std::shared_ptr<User> user,
                                                            std::function<std::unique_ptr<User>(ResultSet)> parseCallback)
    : DbCommand<Connection, ResultSet>(dbConnector), _user(std::move(user)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void DeleteUserCommand<Connection, ResultSet>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _user->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  this->_backUp = std::move(_parseCallback(result));
}

template<typename Connection, typename ResultSet>
void DeleteUserCommand<Connection, ResultSet>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getPassword() + ","
          + _backUp->getEmail() + ");";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet>
void DeleteUserCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _user->getName() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEUSERCOMMAND_H_
