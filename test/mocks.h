//
// Created by Konstantin Pronin on 08.11.2019.
//

#ifndef TASKMANAGER_TEST_INCLUDE_MOCKS_H_
#define TASKMANAGER_TEST_INCLUDE_MOCKS_H_

#include <fstream>
#include <string>

#include <gmock/gmock.h>

#include "database/commands/DbCommand.h"
#include "database/connection/DbConnector.h"
#include "database/factories/DbCommandFactory.h"
#include "database/managers/HistoryManager.h"
#include "entity/Entity.h"
#include "tracking/Notifier.h"
#include "tracking/Subscriber.h"

class MockSubscriber : public Subscriber {
 public:
  MOCK_METHOD(void, update, (Entity & , DbCommand &), (override));
};

class MockEntity : public Entity {};

class MockIfStream : public std::ifstream {
  MOCK_METHOD(bool, is_open, (), ());
};

class MockDbConfig : public DbConfig {
 public:
  MockDbConfig() : DbConfig(MockIfStream()) {}
  MOCK_METHOD(int, getPoolSize, (), (const, override, noexcept));
};

class MockNotifier : public Notifier {
 public:
  MockNotifier(std::vector<Subscriber *> & subs) : Notifier(subs) {};
  MOCK_METHOD(void, notifyAll, (Entity &, DbCommand &), (const, override));
  MOCK_METHOD(void, subscribe, (Subscriber &), (const, override));
  MOCK_METHOD(void, unsubscribe, (Subscriber &), (const, override));
};

class MockHistoryManager : public HistoryManager {
 public:
  MockHistoryManager(DbCommandFactory &factory) : HistoryManager(factory) {}
  MOCK_METHOD(void, push, (DbCommand &), (const, override));
  MOCK_METHOD(DbCommand *, pop, (), (const, override));
};

class MockDbCommand : public DbCommand {
 public:
  MockDbCommand(DbConnector *connector) : DbCommand(connector) {}
  MOCK_METHOD(void, execute, (), (const, override));
  MOCK_METHOD(void, saveBackUp, (), (override));
};

class MockDbCommandFactory : public DbCommandFactory {
 public:
  MOCK_METHOD(DbCommand*, createAddCommand, (Entity), (const, override));
  MOCK_METHOD(DbCommand*, createDeleteCommand, (Entity), (const, override));
  MOCK_METHOD(DbCommand*, createModifyCommand, (Entity), (const, override));
  MOCK_METHOD(DbCommand*, createGetCommand, (long, long), (const, override));
  MOCK_METHOD(DbCommand*, createGetCommand, (std::string), (const, override));
};

class MockDbConnection : public DbConnection {
 public:
  MOCK_METHOD(long, execute, (), ());
};

class MockDbConnector : public DbConnector {
 public:
  MOCK_METHOD(DbConnection *, getConnection, (), (const, override));
  MOCK_METHOD(void, releaseConnection, (), (const, override));
};

#endif //TASKMANAGER_TEST_INCLUDE_MOCKS_H_
