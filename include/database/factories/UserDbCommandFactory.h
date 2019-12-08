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

template<typename Connection, typename ResultSet>
class UserDbCommandFactory : public DbCommandFactory<Connection, ResultSet> {
 private:
  std::function<std::unique_ptr<User>(ResultSet)> _parseCallback;
 public:
  UserDbCommandFactory(DbConnector<Connection, ResultSet> &, std::function<std::unique_ptr<User>(ResultSet)>);
  std::unique_ptr<DbCommand<Connection, ResultSet>> createAddCommand(std::shared_ptr<User>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createDeleteCommand(std::shared_ptr<User>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createModifyCommand(std::shared_ptr<User>) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(long, std::shared_ptr<User>, long) const override;
  std::unique_ptr<DbCommand<Connection, ResultSet>> createGetCommand(std::string, std::shared_ptr<User>) const override;
  ~UserDbCommandFactory() override = default;
};

template<typename Connection, typename ResultSet>
UserDbCommandFactory<Connection, ResultSet>::UserDbCommandFactory(DbConnector<Connection, ResultSet> &dbConnector,
                                                                  std::function<std::unique_ptr<User>(ResultSet)> parseCallback)
    : DbCommandFactory<Connection, ResultSet>(dbConnector), _parseCallback(parseCallback) {}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> UserDbCommandFactory<Connection,
                                                                       ResultSet>::createAddCommand(std::shared_ptr<User> user) const {
  return std::make_unique<AddUserCommand<Connection, ResultSet>>(this->_dbConnector, user);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> UserDbCommandFactory<Connection,
                                                                       ResultSet>::createDeleteCommand(std::shared_ptr<
    User> user) const {
  return std::make_unique<DeleteUserCommand<Connection, ResultSet>>(this->_dbConnector, user, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> UserDbCommandFactory<Connection,
                                                                       ResultSet>::createModifyCommand(std::shared_ptr<
    User> user) const {
  return std::make_unique<ModifyUserCommand<Connection, ResultSet>>(this->_dbConnector, user, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> UserDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(long id,
                                                                                                    std::shared_ptr<User> user,
                                                                                                    long) const {
  return std::make_unique<GetUserByIdCommand<Connection, ResultSet>>(this->_dbConnector, id, user, _parseCallback);
}

template<typename Connection, typename ResultSet>
std::unique_ptr<DbCommand<Connection, ResultSet>> UserDbCommandFactory<Connection,
                                                                       ResultSet>::createGetCommand(std::string name,
                                                                                                    std::shared_ptr<User> user) const {
  return std::make_unique<GetUserByIdCommand<Connection, ResultSet>>(this->_dbConnector, name, user, _parseCallback);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_FACTORIES_USERDBCOMMANDFACTORY_H_
