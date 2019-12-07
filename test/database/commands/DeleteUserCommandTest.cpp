//
//// Created by Konstantin Pronin on 06.12.2019.
////
//
//#include <gtest/gtest.h>
//#include <entities/User.h>
//
//#include "database/commands/user/DeleteUserCommand.h"
//#include "../../mocks.h"
//
//TEST(delete_user_command_test, test_save_back_up) {
//  User user;
//  MockBuffer mockBuffer;
//  MockDbConfig mockConfig(mockBuffer);
//  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
//  MockDbConnector mockConnector(mockConfig);
////  DeleteUserCommand<Flag, Flag> deleteUserCommand(mockConnector, std::make_shared<User>(user));
//
////  deleteUserCommand.saveBackUp();
//
////  ASSERT_EQ(user, *deleteUserCommand.getBackUp());
//}