//
// Created by Konstantin Pronin on 08.11.2019.
//

#ifndef TASKMANAGER_TEST_INCLUDE_MOCKS_H_
#define TASKMANAGER_TEST_INCLUDE_MOCKS_H_

#include <iostream>
#include <string>
#include <vector>

#include <gmock/gmock.h>

#include "database/commands/DbCommand.h"
#include "database/connection/DbConnector.h"
#include "database/factories/DbCommandFactory.h"
#include "managers/HistoryManager.h"
#include "entity/Entity.h"
#include "managers/NotificationManager.h"
#include "tracking/Subscriber.h"

class Flag {
 public:
  bool flag = false;
};

//database mocks
class MockBuffer : public std::streambuf {
  MOCK_METHOD(bool, is_open, (), ());
};

class MockDbConfig : public DbConfig {
 public:
  MockDbConfig(std::streambuf &buf) : DbConfig(buf) {}
  MOCK_METHOD(int, getPoolSize, (), (const, override, noexcept));
};

class MockDbCommand : public DbCommand<Flag, Flag> {
 public:
  MockDbCommand(const DbConnector<Flag, Flag> &connector) : DbCommand<Flag, Flag>(connector) {}
  MockDbCommand(const MockDbCommand &command) : DbCommand(command) {}
  MOCK_METHOD(void, execute, (), (const, override));
  MOCK_METHOD(void, saveBackUp, (), (override));
  MOCK_METHOD(void, undo, (), (const, override));
};

class MockDbConnection : public DbConnection<Flag, Flag> {
 public:
  MOCK_METHOD(std::vector<std::string>* , execute, (), ());
};

class MockDbConnector : public DbConnector<Flag, Flag> {
 public:
  MockDbConnector(const DbConfig &conf) : DbConnector<Flag, Flag> (conf) {}
//  MOCK_METHOD(std::unique_ptr<DbConnection<int, int>>, getConnection, (), (const, override));
//  MOCK_METHOD(void, releaseConnection, (std::unique_ptr<DbConnection<int, int>> &&), (const, override));
};

//class MockDbCommandFactory : public DbCommandFactory {
// public:
//  MOCK_METHOD(DbCommand*, createAddCommand, (Entity), (const, override));
//  MOCK_METHOD(DbCommand*, createDeleteCommand, (Entity), (const, override));
//  MOCK_METHOD(DbCommand*, createModifyCommand, (Entity), (const, override));
//  MOCK_METHOD(DbCommand*, createGetCommand, (long, long), (const, override));
//  MOCK_METHOD(DbCommand*, createGetCommand, (std::string), (const, override));
//};

//managers mocks
//class MockNotificationManager : public NotificationManager {
// public:
//  MockNotificationManager(std::vector<std::shared_ptr<Subscriber>> subs) : NotificationManager(subs) {};
//  MOCK_METHOD(void, notifyAll, (Entity &, Entity &), (const, override));
//  MOCK_METHOD(void, subscribe, (std::shared_ptr<Subscriber>), (override));
//  MOCK_METHOD(void, unsubscribe, (std::shared_ptr<Subscriber>), (override));
//};
//
//class MockHistoryManager : public HistoryManager {
// public:
//  MockHistoryManager() : HistoryManager([](std::shared_ptr<Entity>){}, [](){return nullptr;}) {}
//  MOCK_METHOD(void, push, (std::shared_ptr<Entity>), (const, override));
//  MOCK_METHOD(std::shared_ptr<Entity>, pop, (), (const, override));
//};

//tracking mocks
class MockSubscriber : public Subscriber {
 public:
  MOCK_METHOD(void, update, (const Entity &, const Entity &), (override));
};
#endif //TASKMANAGER_TEST_INCLUDE_MOCKS_H_
