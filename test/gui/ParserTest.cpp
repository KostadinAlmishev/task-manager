// ---- Parser testing ---- //

TEST(ParserTest, ParserTestGroup) {
std::string str = "get-group-by-name frontend";
Parser parser;
EntityContainer * ec = parser.parseGroupEntity(str);
EXPECT_EQ(ec->mode, 0);
EXPECT_TRUE(ec->group != NULL);
}
TEST(ParserTest, ParserTestGroupList) {
std::string str = "get-project-by-id 12";
Parser parser;
EntityContainer * ec = parser.parseGroupEntity(str);
EXPECT_EQ(ec->mode, 1);
EXPECT_TRUE(ec->project != NULL);
}
TEST(ParserTest, ParserTestProject) {
std::string str = "get-project-by-id 12";
Parser parser;
EntityContainer * ec = parser.parseProjectEntity(str);
EXPECT_EQ(ec->mode, 2);
EXPECT_TRUE(ec->project != NULL);
}
TEST(ParserTest, ParserTestProjectList) {
std::string str = "get-all-project-of-user Popov";
Parser parser;
EntityContainer * ec = parser.parseProjectEntity(str);
EXPECT_EQ(ec->mode, 3);
EXPECT_TRUE(ec->projectList != NULL);
}
TEST(ParserTest, ParserTestUser) {
std::string str = "get-user-by-id Popov";
Parser parser;
EntityContainer * ec = parser.parseUserEntity(str);
EXPECT_EQ(ec->mode, 4);
EXPECT_TRUE(ec->user != NULL);
}
TEST(ParserTest, ParserTestUserList) {
std::string str = "find-users-by-project-name Twitter-script";
Parser parser;
EntityContainer * ec = parser.parseUserEntity(str);
EXPECT_EQ(ec->mode, 5);
EXPECT_TRUE(ec->user != NULL);
}
TEST(ParserTest, ParserTestTask) {
std::string str = "get-task-by-task-id 3";
Parser parser;
EntityContainer * ec = parser.parseUserEntity(str);
EXPECT_EQ(ec->mode, 6);
EXPECT_TRUE(ec->task != NULL);
}
TEST(ParserTest, ParserTestTaskList) {
std::string str = "find-tasks-by-project-name Twitter-script";
Parser parser;
EntityContainer * ec = parser.parseUserEntity(str);
EXPECT_EQ(ec->mode, 7);
EXPECT_TRUE(ec->taskList != NULL);
}
TEST(ParserTest, ParserTestParse) {
std::string str = "task get-task-by-task-id 3";
Parser parser;
EntityContainer * ec = parser.parse(str);
EXPECT_EQ(ec->mode, 6);
EXPECT_TRUE(ec->task != NULL);
}
