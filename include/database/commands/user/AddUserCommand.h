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

template<typename Callback>
class AddUserCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _user;

 public:
  AddUserCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddUserCommand() = default;
};

template<typename Callback>
AddUserCommand<Callback>::AddUserCommand(DbConnector<Callback> &dbConnector,
                                         std::shared_ptr<Entity> user)
    : DbCommand<Callback>(dbConnector), _user(std::move(user)) {}

template<typename Callback>
void AddUserCommand<Callback>::saveBackUp() {}

template<typename Callback>
void AddUserCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _user->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"USERS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void AddUserCommand<Callback>::execute() const {
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
