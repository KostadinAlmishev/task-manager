//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <gtest/gtest.h>

#include "database/managers/HistoryManager.h"
#include "../../mocks.h"

TEST(history_manager_test, test_push) {
  MockDbConfig mockConfig;
  MockDbCommand mockCommand(DbConnector::getInstance(mockConfig));
  MockDbCommandFactory mockFactory;
  HistoryManager history(mockFactory);
  ON_CALL(mockFactory, createAddCommand(Entity())).WillByDefault(testing::Return(&mockCommand));

  history.push(mockCommand);

  EXPECT_CALL(mockCommand, execute()).Times(1);
}

TEST(history_manager_test, test_pop) {
  MockDbConfig mockConfig;
  MockDbCommand mockCommand(DbConnector::getInstance(mockConfig));
  MockDbCommandFactory mockFactory;
  HistoryManager history(mockFactory);

  ON_CALL(mockFactory, createGetCommand(-1, 0)).WillByDefault(testing::Return(&mockCommand));

  history.pop();

  EXPECT_CALL(mockCommand, execute()).Times(1);
}