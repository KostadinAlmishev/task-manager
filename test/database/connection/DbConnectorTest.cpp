//
// Created by Konstantin Pronin on 07.11.2019.
//

#include "../../mocks.h"

TEST(db_connector_test, test_get_connection) {
  MockBuffer mockBuffer;
  MockDbConfig mockConfig(mockBuffer);
  DbConnector<Flag, Flag> dbConnector(mockConfig);

  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
  dbConnector.initializeConnectionPool([](const DbConfig &conf) {return nullptr;},
      [](Flag a, std::string s) {return nullptr;}, [](std::unique_ptr<Flag> &&){});

  auto dbConnection = dbConnector.getConnection();

  ASSERT_TRUE(dbConnection != nullptr);
}

TEST(db_connector_test, test_release_connection) {
  MockBuffer mockBuffer;
  MockDbConfig mockConfig(mockBuffer);
  DbConnector<Flag, Flag> dbConnector(mockConfig);

  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
  dbConnector.initializeConnectionPool([](const DbConfig &conf) {return nullptr;},
                                       [](Flag a, std::string s) {return nullptr;}, [](std::unique_ptr<Flag> &&){});
  auto dbConnection = dbConnector.getConnection();
  dbConnector.releaseConnection(std::move(dbConnection));

  ASSERT_TRUE(dbConnector.getConnection() != nullptr);
}

