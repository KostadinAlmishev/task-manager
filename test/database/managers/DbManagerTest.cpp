//
// Created by Konstantin Pronin on 07.11.2019.
//

#include "../../mocks.h"
#include "database/managers/DbManager.h"

TEST(db_manager_test, test_execute_command) {
  std::vector<Subscriber *> subs;
  MockDbConfig mockDbConfig;
  MockDbCommand mockCommand(DbConnector::getInstance(mockDbConfig));
  MockNotifier mockNotifier(subs);
  MockDbCommandFactory mockFactory;
  MockHistoryManager mockHistory(mockFactory);
  DbManager dbManager(mockHistory, mockNotifier);

  dbManager.setCommand(mockCommand);

  EXPECT_CALL(mockCommand,execute()).Times(1);
  EXPECT_CALL(mockHistory, push(mockCommand)).Times(1);
}