//
// Created by Konstantin Pronin on 07.11.2019.
//

#include <sstream>

#include <gtest/gtest.h>

#include "database/config/DbConfig.h"

TEST(db_config_test, test_read_config) {
  std::string mockValues = "host=testHost\nport=0000\nname=testDb\nuser=testLogin\npassword=testpass\npool=0";
  std::stringbuf testStream(mockValues);
  DbConfig config(testStream);

  config.readConfigFromFile();

  ASSERT_EQ("testHost", config.getHost());
  ASSERT_EQ("0000", config.getPort());
  ASSERT_EQ("testDb", config.getDbName());
  ASSERT_EQ("testLogin", config.getUser());
  ASSERT_EQ("testpass", config.getPassword());
  ASSERT_EQ(0, config.getPoolSize());
}
