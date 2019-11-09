//
// Created by Konstantin Pronin on 07.11.2019.
//

#include "../../mocks.h"

TEST(db_connector_test, test_get_connection) {
  MockDbConfig mockConfig;
  DbConnector *dbConnector = DbConnector::getInstance(mockConfig);

  DbConnection *dbConnection = dbConnector->getConnection();

  ASSERT_TRUE(dbConnection != nullptr);
}

TEST(db_connector_test, test_release_connection) {
  MockDbConfig mockConfig;
  DbConnector *dbConnector = DbConnector::getInstance(mockConfig);

  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
  dbConnector->getConnection();
  dbConnector->releaseConnection();

  ASSERT_TRUE(dbConnector->getConnection() != nullptr);
}

