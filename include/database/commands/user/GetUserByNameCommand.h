//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/User.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet, typename Callback>
class GetUserByNameCommand : public DbCommand<Connection, ResultSet, Callback> {
 private:
  std::string _name;
  std::shared_ptr<Entity> &_user;

 public:
  GetUserByNameCommand(DbConnector<Connection, ResultSet, Callback> &,
                       std::string,
                       std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByNameCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
GetUserByNameCommand<Connection, ResultSet, Callback>::GetUserByNameCommand(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector,
                                                                            std::string name,
                                                                            std::shared_ptr<Entity> &user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector),
      _name(std::move(name)),
      _user(user) {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByNameCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByNameCommand<Connection, ResultSet, Callback>::undo() const {}

template<typename Connection, typename ResultSet, typename Callback>
void GetUserByNameCommand<Connection, ResultSet, Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where NAME = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  _user = std::move(Callback::parseToUser(result));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_
