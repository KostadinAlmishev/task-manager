//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/User.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class GetUserByIdCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  long _id;
  std::shared_ptr<User> _user;

 public:
  GetUserByIdCommand(DbConnector<Connection, ResultSet, Callback> &,
                     long,
                     std::shared_ptr<User>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByIdCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetUserByIdCommand<Connection, ResultSet, Callback>::GetUserByIdCommand(DbConnector<Connection,
                                                                                    ResultSet,
                                                                                    Callback> &dbConnector,
                                                                        long id,
                                                                        std::shared_ptr<User> user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _id(id),
      _user(std::move(user)) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByIdCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByIdCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByIdCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"ID\" = \'" + _id
          + "\';";
  auto result = this->executeQuery(sql);
  *_user = *Callback::parseToUser(result);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
