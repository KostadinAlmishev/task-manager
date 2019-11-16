#include "gtest/gtest.h"
#include <iostream>


class Display;
class Gui;
class Parser;
class EntityContainer;
class ServiceConnector;

class GroupService;
class ProjectService;
class UserService;
class TaskService;

class Entity;
class Group;
class Project;
class User;
class Task;

class EntityContainer {
private:

public:
    // here will be meta data

    int mode;
    Group * group;
    std::vector<Group> * groupList;
    Project * project;
    std::vector<Project> * projectList;
    User * user;
    std::vector<User> * userList;
    Task * task;
    std::vector<Task> * taskList;
};


// ---- Gui testing ---- //

class Gui {
private:
    Parser * parser;
    ServiceConnector * serviceConnector;

    std::string readCommand();
    EntityContainer * parse(std::string);
    bool sendCommand(EntityContainer * entityContainer);
    //    methods of getting info from back
public:
    bool runGui();
};

bool Gui::runGui() {
    return true;
}

TEST(GuiTest, GuiTestRunning) {
    Gui gui;
    EXPECT_TRUE(gui.runGui());
}

// ---- Display testing ---- //

class Display {
private:
    size_t _width;
    size_t _height;


    static Display * p_instance;

    Display(int width, int height);
    Display(const Display& other) = delete;
    Display& operator=(const Display&) = delete;
public:

    static Display * instance(size_t width, size_t height) {
        if(!p_instance) {
            p_instance = new Display(width, height);
        }
        return p_instance;
    }

    std::string getCommandFromUser();
    void printText(std::string body);
    size_t width() const;
    size_t height() const;
};

Display * Display::p_instance = NULL;

Display::Display(int width, int height) {
    _width = width;
    _height = height;
}
std::string Display::getCommandFromUser() {
    std::string str = "some text from user";
    return str;
}
void Display::printText(std::string body) {
    std::cout << body;
}
size_t Display::width() const {
    return _width;
}
size_t Display::height() const {
    return _height;
}

TEST(DisplayTest, DisplayTestWidth) {
    Display * d = Display::instance(100, 100);
}

TEST(Display, DisplayInstance) {
    Display * d1 = Display::instance(100, 100);
    Display * d2 = Display::instance(200, 200);
    EXPECT_EQ(d1, d2);
}



// ---- Parser testing ---- //

class Parser {
private:

public:
    EntityContainer * parseProjectEntity(std::string command);
    EntityContainer * parseTaskEntity(std::string command);
    EntityContainer * parseUserEntity(std::string command);
    EntityContainer * parseGroupEntity(std::string command);
    EntityContainer * parse(std::string command);
};

EntityContainer * Parser::parseProjectEntity(std::string command) {
    EntityContainer * ec = new EntityContainer;
    return ec;
}
EntityContainer * Parser::parseTaskEntity(std::string command) {
    EntityContainer * ec = new EntityContainer;
    return ec;
}
EntityContainer * Parser::parseUserEntity(std::string command) {
    EntityContainer * ec = new EntityContainer;
    return ec;
}
EntityContainer * Parser::parseGroupEntity(std::string command) {
    EntityContainer * ec = new EntityContainer;
    return ec;
}
EntityContainer * Parser::parse(std::string command) {
    EntityContainer * ec = new EntityContainer;
    return ec;
}

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

class ServiceConnector {
private:
    ProjectService *projectService;
    TaskService *taskService;
    UserService *userService;
    GroupService *groupService;
public:
    ServiceConnector(ProjectService *projectService,
                     TaskService *taskService,
                     UserService *userService,
                     GroupService *groupService);

    void getEntityFromBack(EntityContainer *entityContainer);

    void sendEntityToBack(EntityContainer *entityContainer);
};




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}