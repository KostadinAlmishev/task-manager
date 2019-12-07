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
#include "entities/Entity.h"
#include "managers/NotificationManager.h"
#include "tracking/Subscriber.h"

class Flag {
 public:
  bool flag = false;
};

//database mocks
//class MockDbConfig : public DbConfig {
// public:
//  MockDbConfig(std::streambuf &buf) : DbConfig(buf) {}
//  MOCK_METHOD(int, getPoolSize, (), (const, override, noexcept));
//};

//class MockDbCommand : public DbCommand<Flag, Flag> {
// public:
//  MockDbCommand(DbConnector<Flag, Flag> &connector) : DbCommand<Flag, Flag>(connector) {}
//  MockDbCommand(const MockDbCommand &command) : DbCommand(command) {}
//  MOCK_METHOD(void, execute, (), (const, override));
//  MOCK_METHOD(void, saveBackUp, (), (override));
//  MOCK_METHOD(void, undo, (), (const, override));
//};
//
//class MockDbConnection : public DbConnection<Flag, Flag> {
// public:
//  MOCK_METHOD(std::vector<std::string>* , execute, (), ());
//};
//
//class MockDbConnector : public DbConnector<Flag, Flag> {
// public:
//  MockDbConnector(const DbConfig &conf) : DbConnector<Flag, Flag>(conf) {}
//  MOCK_METHOD((std::unique_ptr<DbConnection<Flag, Flag>>), getConnection, (), (override));
//  MOCK_METHOD(void, releaseConnection, ((std::unique_ptr<DbConnection<Flag, Flag>>) &&), (override));
//};
//
////tracking mocks
//class MockSubscriber : public Subscriber {
// public:
//  MOCK_METHOD(void, update, (const User &, const Entity &), (override));
//};
#endif //TASKMANAGER_TEST_INCLUDE_MOCKS_H_
