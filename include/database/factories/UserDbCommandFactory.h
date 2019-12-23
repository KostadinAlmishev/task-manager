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

template<typename Connection, typename ResultSet, typename Callback>
class UserDbCommandFactory : public DbCommandFactory<Connection, ResultSet, Callback> {
 public:
  UserDbCommandFactory(DbConnector<Connection, ResultSet, Callback> &);
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

template<typename Connection, typename ResultSet, typename Callback>
UserDbCommandFactory<Connection, ResultSet, Callback>::UserDbCommandFactory(DbConnector<Connection,
                                                                                        ResultSet,
                                                                                        Callback> &dbConnector)
    : DbCommandFactory<Connection, ResultSet, Callback>(dbConnector) {}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createAddCommand(
    std::shared_ptr<Entity> user) const {
  return std::make_unique<AddUserCommand<Connection, ResultSet, Callback>>(this->_dbConnector, user);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Connection,
                                                                                 ResultSet,
                                                                                 Callback>::createDeleteCommand(std::shared_ptr<Entity> user) const {
  return std::make_unique<DeleteUserCommand<Connection, ResultSet, Callback>>(this->_dbConnector, user);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Connection,
                                                                                 ResultSet,
                                                                                 Callback>::createModifyCommand(std::shared_ptr<Entity> user) const {
  return std::make_unique<ModifyUserCommand<Connection, ResultSet, Callback>>(this->_dbConnector, user);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createGetCommand(
    long id,
    std::shared_ptr<Entity> &user,
    long) const {
  return std::make_unique<GetUserByIdCommand<Connection, ResultSet, Callback>>(this->_dbConnector, id, user);
}

template<typename Connection, typename ResultSet, typename Callback>
std::unique_ptr<IDbCommand> UserDbCommandFactory<Connection,
                                                                                 ResultSet, Callback>::createGetCommand(
    std::string name,
    std::shared_ptr<Entity> &user) const {
  return std::make_unique<GetUserByNameCommand<Connection, ResultSet, Callback>>(this->_dbConnector, name, user);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_USERDBCOMMANDFACTORY_H_
