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

template<typename Callback>
class DeleteUserCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _user;
  std::unique_ptr<User> _backUp;

 public:
  DeleteUserCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteUserCommand() = default;
};

template<typename Callback>
DeleteUserCommand<Callback>::DeleteUserCommand(DbConnector<Callback> &dbConnector,
                                               std::shared_ptr<Entity> user)
    : DbCommand<Callback>(dbConnector), _user(std::move(user)) {}

template<typename Callback>
void DeleteUserCommand<Callback>::saveBackUp() {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToUser(result));
}

template<typename Callback>
void DeleteUserCommand<Callback>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"USERS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getPassword() + ","
          + _backUp->getEmail() + ");";
  this->executeQuery(sql);
}

template<typename Callback>
void DeleteUserCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEUSERCOMMAND_H_
