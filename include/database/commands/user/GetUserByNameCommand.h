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
template<typename Connection, typename ResultSet>
class GetUserByNameCommand : public DbCommand<Connection, ResultSet> {
 private:
  std::string _name;
  std::shared_ptr<User> _user;
  std::function<std::unique_ptr<User>(ResultSet)> _parseCallback;

 public:
  GetUserByNameCommand(DbConnector<Connection, ResultSet> &,
                       std::string,
                       std::shared_ptr<User>,
                       std::function<std::unique_ptr<User>(ResultSet)>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByNameCommand() = default;
};

template<typename Connection, typename ResultSet>
GetUserByNameCommand<Connection, ResultSet>::GetUserByNameCommand(DbConnector<Connection, ResultSet> &dbConnector,
                                                                  std::string name,
                                                                  std::shared_ptr<User> user,
                                                                  std::function<std::unique_ptr<User>(ResultSet)> parseCallback)
    : DbCommand<Connection, ResultSet>(dbConnector),
      _name(std::move(name)),
      _user(std::move(user)),
      _parseCallback(std::move(parseCallback)) {}

template<typename Connection, typename ResultSet>
void GetUserByNameCommand<Connection, ResultSet>::saveBackUp() {}

template<typename Connection, typename ResultSet>
void GetUserByNameCommand<Connection, ResultSet>::undo() const {}

template<typename Connection, typename ResultSet>
void GetUserByNameCommand<Connection, ResultSet>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \"NAME\" = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  *_user = *_parseCallback(result);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_
