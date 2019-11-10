//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <gtest/gtest.h>

#include "database/managers/HistoryManager.h"
#include "../../mocks.h"

TEST(history_manager_test, test_push) {
  MockDbConfig mockConfig;
  MockDbConnector mockConnector(mockConfig);
  MockDbCommand mockCommand(&mockConnector);
  MockDbCommandFactory mockFactory;
  HistoryManager history(mockFactory);
  ON_CALL(mockFactory, createAddCommand(::testing::_)).WillByDefault(testing::Return(&mockCommand));

  history.push(mockCommand);

  EXPECT_CALL(mockCommand, execute()).Times(1);
}

TEST(history_manager_test, test_pop) {
  MockDbConfig mockConfig;
  MockDbConnector mockConnector(mockConfig);
  MockDbCommand mockCommand(&mockConnector);
  MockDbCommandFactory mockFactory;
  HistoryManager history(mockFactory);

  ON_CALL(mockFactory, createGetCommand(::testing::_, ::testing::_)).WillByDefault(testing::Return(&mockCommand));

  history.pop();

  EXPECT_CALL(mockCommand, execute()).Times(1);
}