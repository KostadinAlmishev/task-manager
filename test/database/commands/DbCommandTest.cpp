//
// Created by Konstantin Pronin on 07.11.2019.
//
#include <gtest/gtest.h>

#include "database/commands/DeleteProjectCommand.h"
#include "../../mocks.h"

TEST(delete_project_command_test, test_save_back_up) {
  MockEntity mockEntity;
  MockDbConfig mockConf;
  MockDbConnection mockConnection;
  MockDbConnector mockConnector;
  DeleteProjectCommand command(mockConnector);

  ON_CALL(*mockConnector, getConnection()).WillByDefault(testing::Return(&mockConnection));
  ON_CALL(mockConnection, execute()).WillByDefault(testing::Return(mockEntity));

  command.saveBackUp();

  ASSERT_EQ(mockEntity, command.getBackUp());
}

TEST(delete_project_command_test, test_execute) {
  MockDbConfig mockConf;
  MockDbConnection mockConnection;
  MockDbConnector mockConnector;
  DeleteProjectCommand command(mockConnector);

  ON_CALL(*mockConnector, getConnection()).WillByDefault(testing::Return(&mockConnection));

  command.execute();

  EXPECT_CALL(mockConnection, execute()).Times(1);
}