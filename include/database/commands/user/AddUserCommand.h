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
template<typename Connection, typename ResultSet, typename Callback>
class AddUserCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<User> _user;
  std::unique_ptr<User> _backUp;

 public:
  AddUserCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<User>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddUserCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
AddUserCommand<Connection, ResultSet, Callback>::AddUserCommand(DbConnector<Connection,
                                                                            ResultSet,
                                                                            Callback> &dbConnector,
                                                                std::shared_ptr<User> user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _user(std::move(user)) {}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::saveBackUp() {
  _backUp = std::make_unique(*_user);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _backUp->getName()
          + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" VALUES ("
          + _user->getName() + ","
          + _user->getPassword() + ","
          + _user->getEmail() + ");";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_ADDUSERCOMMAND_H_
