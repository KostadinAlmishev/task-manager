//
// Created by Konstantin Pronin on 03.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/User.h"

template<typename Callback>
class GetUserByIdCommand : public DbCommand<Callback> {
 private:
  long _id;
  std::shared_ptr<Entity> &_user;

 public:
  GetUserByIdCommand(DbConnector<Callback> &,
                     long,
                     std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetUserByIdCommand() = default;
};

template<typename Callback>
GetUserByIdCommand<Callback>::GetUserByIdCommand(DbConnector<Callback> &dbConnector,
                                                 long id,
                                                 std::shared_ptr<Entity> &user)
    : DbCommand<Callback>(dbConnector),
      _id(id),
      _user(user) {}

template<typename Callback>
void GetUserByIdCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetUserByIdCommand<Callback>::undo() const {}

template<typename Callback>
void GetUserByIdCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where ID = \'" + std::to_string(_id)
          + "\';";
  auto result = this->executeQuery(sql);
  _user = std::move(Callback::parseToUser(result));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_USER_GETUSERBYIDCOMMAND_H_
