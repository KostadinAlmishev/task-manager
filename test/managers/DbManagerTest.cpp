////
//// Created by Konstantin Pronin on 07.11.2019.
////
//
//#include <memory>
//
//#include "../mocks.h"
//#include "managers/DbManager.h"
//
//TEST(db_manager_test, test_execute_command) {
//  MockBuffer mockBuffer;
//  MockDbConfig mockConfig(mockBuffer);
//  ON_CALL(mockConfig, getPoolSize()).WillByDefault(::testing::Return(1));
//  MockDbConnector mockConnector(mockConfig);
//  MockDbCommand mockCommand(mockConnector);
//
//  DbManager<Flag, Flag> dbManager;
//
//  dbManager.setCommand(std::make_shared<MockDbCommand>(mockCommand));
//  dbManager.executeCommand();
//
//  EXPECT_CALL(mockCommand,execute()).Times(1);
//}