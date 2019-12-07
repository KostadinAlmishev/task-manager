//
// Created by Konstantin Pronin on 03.12.2019.
//

#include <gtest/gtest.h>

#include "database/commands/user/AddUserCommand.h"
#include "../../mocks.h"

TEST(add_user_command_test, test_save_back_up) {
  User user;
  MockBuffer mockBuffer;
  MockDbConfig mockConfig(mockBuffer);
  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
  MockDbConnector mockConnector(mockConfig);
  AddUserCommand<Flag, Flag> addUserCommand(mockConnector, std::make_shared<User>(user));
  
  addUserCommand.saveBackUp();
  
//  ASSERT_EQ(user, *addUserCommand.getBackUp());
}