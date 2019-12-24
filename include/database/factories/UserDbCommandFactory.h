//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_FACTORIES_USERDBCOMMANDFACTORY_H_
#define TASKMANAGER_INCLUDE_DATABASE_FACTORIES_USERDBCOMMANDFACTORY_H_

#include "database/commands/user/AddUserCommand.h"
#include "database/commands/user/DeleteUserCommand.h"
#include "database/commands/user/GetUserByIdCommand.h"
#include "database/commands/user/GetUserByNameCommand.h"
#include "database/commands/user/ModifyUserCommand.h"
#include "database/factories/DbCommandFactory.h"
#include "entities/User.h"

template<typename Callback>
class UserDbCommandFactory : public DbCommandFactory<Callback> {
 public:
  UserDbCommandFactory(DbConnector<Callback> &);
  std::unique_ptr<IDbCommand> createAddCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createDeleteCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createModifyCommand(std::shared_ptr<Entity>) const override;
  std::unique_ptr<IDbCommand> createGetCommand(long,
                                               std::shared_ptr<Entity> &,
                                               long) const override;
  std::unique_ptr<IDbCommand> createGetCommand(std::string,
                                               std::shared_ptr<Entity> &) const override;
  ~UserDbCommandFactory() override = default;
};

template<typename Callback>
UserDbCommandFactory<Callback>::UserDbCommandFactory(DbConnector<Callback> &dbConnector)
    : DbCommandFactory<Callback>(dbConnector) {}

template<typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Callback>::createAddCommand(
    std::shared_ptr<Entity> user) const {
  return std::make_unique<AddUserCommand<Callback>>(this->_dbConnector, user);
}

template<typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Callback>::createDeleteCommand(std::shared_ptr<Entity> user) const {
  return std::make_unique<DeleteUserCommand<Callback>>(this->_dbConnector, user);
}

template<typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Callback>::createModifyCommand(std::shared_ptr<Entity> user) const {
  return std::make_unique<ModifyUserCommand<Callback>>(this->_dbConnector, user);
}

template<typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Callback>::createGetCommand(
    long id,
    std::shared_ptr<Entity> &user,
    long) const {
  return std::make_unique<GetUserByIdCommand<Callback>>(this->_dbConnector, id, user);
}

template<typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Callback>::createGetCommand(
    std::string name,
    std::shared_ptr<Entity> &user) const {
  return std::make_unique<GetUserByNameCommand<Callback>>(this->_dbConnector, name, user);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_USERDBCOMMANDFACTORY_H_
