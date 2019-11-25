//
// Created by kotik on 25.11.2019.
//

#include "gtest/gtest.h"

#include <iostream>


#include "Entities.h"
#include "Services.h"
#include "EntityContainer.h"
#include "Gui.h"
#include "Display.h"
#include "ServiceConnector.h"
#include "Parser.h"




// ---- Gui testing ---- //

TEST(GuiTest, GuiTestRunning) {
    Gui gui;
    EXPECT_TRUE(gui.runGui());
}

// ---- Display testing ---- //

TEST(DisplayTest, DisplayTestWidth) {
    Display * d = Display::instance(100, 100);
}

TEST(Display, DisplayInstance) {
    Display * d1 = Display::instance(100, 100);
    Display * d2 = Display::instance(200, 200);
    EXPECT_EQ(d1, d2);
}

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

// ---- ServiceConnector testing ---- //






int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}