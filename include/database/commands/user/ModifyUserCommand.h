//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_MODIFYUSERCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_MODIFYUSERCOMMAND_H_

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
class ModifyUserCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::shared_ptr<User> _user;
  std::unique_ptr<User> _backUp;

 public:
  ModifyUserCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<User>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyUserCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
ModifyUserCommand<Connection, ResultSet, Callback>::ModifyUserCommand(DbConnector<Connection,
                                                                                  ResultSet,
                                                                                  Callback> &dbConnector,
                                                                      std::shared_ptr<User> user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _user(std::move(user)) {}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyUserCommand<Connection, ResultSet, Callback>::saveBackUp() {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _user->getName()
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToUser(result));
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyUserCommand<Connection, ResultSet, Callback>::undo() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"USERS\" set \"NAME\" = \'"
          + _backUp->getName() + "\', \"PASSWORD\" = \'"
          + _backUp->getPassword() + "\', \"EMAIL\" = \'"
          + _backUp->getEmail() + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void ModifyUserCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"USERS\" set \"NAME\" = \'"
          + _user->getName() + "\', \"PASSWORD\" = \'"
          + _user->getPassword() + "\', \"EMAIL\" = \'"
          + _user->getEmail() + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_MODIFYUSERCOMMAND_H_
