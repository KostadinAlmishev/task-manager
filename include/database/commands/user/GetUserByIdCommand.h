//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include <entity/User.h>

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class GetUserByIdCommand : public DbCommand<Connection, ResultSet> {
 private:
  long _id;
  std::shared_ptr<User> _user;
  std::function<User(ResultSet)> _parseCallback;

 public:
  GetUserByIdCommand(long, std::shared_ptr<User>, std::function<User(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByIdCommand() = default;
};

template<typename Connection, typename ResultSet>
GetUserByIdCommand<Connection, ResultSet>::GetUserByIdCommand(long id,
                                                              std::shared_ptr<User> user,
                                                              std::function<User(ResultSet)> parseCallback)
    : _id(id), _user(std::move(user)), _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void GetUserByIdCommand<Connection, ResultSet>::saveBackUp() {}

template<typename Connection, typename ResultSet>
void GetUserByIdCommand<Connection, ResultSet>::undo() const {}

template<typename Connection, typename ResultSet>
void GetUserByIdCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"ID\" = \'" + _id
          + "\';";
  auto dbConnection = this->_dbConnector.getConnection();
  auto connection = dbConnection->connect();
  auto result = dbConnection->execute(*connection, sql);
  this->_backUp = _parseCallback(result);
  dbConnection->free(connection);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
