//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/User.h"

template<typename Callback>
class GetUserByNameCommand : public DbCommand<Callback> {
 private:
  std::string _name;
  std::shared_ptr<Entity> &_user;

 public:
  GetUserByNameCommand(DbConnector<Callback> &,
                       std::string,
                       std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByNameCommand() = default;
};

template<typename Callback>
GetUserByNameCommand<Callback>::GetUserByNameCommand(DbConnector<Callback> &dbConnector,
                                                     std::string name,
                                                     std::shared_ptr<Entity> &user)
    : DbCommand<Callback>(dbConnector),
      _name(std::move(name)),
      _user(user) {}

template<typename Callback>
void GetUserByNameCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetUserByNameCommand<Callback>::undo() const {}

template<typename Callback>
void GetUserByNameCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where NAME = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  _user = std::move(Callback::parseToUser(result));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYNAMECOMMAND_H_
