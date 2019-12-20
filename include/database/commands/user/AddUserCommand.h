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
  std::shared_ptr<Entity> _user;

 public:
  AddUserCommand(DbConnector<Connection, ResultSet, Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddUserCommand() = default;
};

template<typename Connection, typename ResultSet, typename Callback>
AddUserCommand<Connection, ResultSet, Callback>::AddUserCommand(DbConnector<Connection,
                                                                            ResultSet,
                                                                            Callback> &dbConnector,
                                                                std::shared_ptr<Entity> user)
    : DbCommand<Connection, ResultSet, Callback>(dbConnector), _user(std::move(user)) {}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::saveBackUp() {}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::undo() const {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where \""
          + descriptors[1].field + "\" = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

template<typename Connection, typename ResultSet, typename Callback>
void AddUserCommand<Connection, ResultSet, Callback>::execute() const {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" ("
          + descriptors[1].field + ", "
          + descriptors[2].field + ", "
          + descriptors[3].field + ") VALUES (\'"
          + descriptors[1].value + "\',\'"
          + descriptors[2].value + "\',\'"
          + descriptors[3].value + "\');";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_ADDUSERCOMMAND_H_
