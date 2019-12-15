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
template<typename Connection, typename ResultSet, typename Callback>
class DeleteUserCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<User> _user;
  std::unique_ptr<User> _backUp;

 public:
  DeleteUserCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<User>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteUserCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
DeleteUserCommand<Connection, ResultSet, Callback>::DeleteUserCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<User> user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _user(std::move(user)) {}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteUserCommand<Connection, ResultSet, Callback>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _user->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToUser(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteUserCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getPassword() + ","
          + _backUp->getEmail() + ");";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void DeleteUserCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _user->getName() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEUSERCOMMAND_H_
