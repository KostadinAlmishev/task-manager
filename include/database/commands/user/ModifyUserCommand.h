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

template<typename Callback>
class ModifyUserCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _user;
  std::unique_ptr<User> _backUp;

 public:
  ModifyUserCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyUserCommand() = default;
};

template<typename Callback>
ModifyUserCommand<Callback>::ModifyUserCommand(DbConnector<Callback> &dbConnector,
                                               std::shared_ptr<Entity> user)
    : DbCommand<Callback>(dbConnector), _user(std::move(user)) {}

template<typename Callback>
void ModifyUserCommand<Callback>::saveBackUp() {
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
void ModifyUserCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _backUp->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"USERS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void ModifyUserCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"USERS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_MODIFYUSERCOMMAND_H_
