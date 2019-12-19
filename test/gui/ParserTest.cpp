#include "gtest/gtest.h"
#include "gui/Parser.h"
#include "entities/Entity.h"
#include "entities/Request.h"
#include <iostream>
#include <string>



// ---- Parse authorization test ---- //

TEST(ParserTest, SignIn) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "   sign-in   ";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::AUTHORIZATION);
    EXPECT_EQ(request->code, requestCode::_EMPTY);
    EXPECT_EQ(request->findBy, requestFindBy::_EMPTY);
}

TEST(ParserTest, SignOut) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "sign-out  ";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::DEAUTHORIZATION);
    EXPECT_EQ(request->code, requestCode::_EMPTY);
    EXPECT_EQ(request->findBy, requestFindBy::_EMPTY);
}

// ---- Parse authorization bad command ---- //

TEST(ParserTest, SignInBaCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "sign-out admin ";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

TEST(ParserTest, SignOutBaCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "   sign-in admin ";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

// ---- Parse task test ---- //

TEST(ParserTest, TaskGetById) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "task get-by-id 1";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::GET);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::ID);
    EXPECT_EQ(request->task->getId(), 1);
}

TEST(ParserTest, TaskGetByName) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(task get-by-name "  first task "  )";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::GET);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::NAME);
    EXPECT_EQ(request->task->getName(), "first task");
}

TEST(ParserTest, TaskSave) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "  task    new  ";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::SAVE);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::_EMPTY);
}

TEST(ParserTest, TaskDeleteById) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = "  task delete-by-id 5  ";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::DELETE);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::ID);
    EXPECT_EQ(request->task->getId(), 5);
}

TEST(ParserTest, TaskDeleteByName) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task delete-by-name 'bad task '  )";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::DELETE);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::NAME);
    EXPECT_EQ(request->task->getName(), "bad task");
}

TEST(ParserTest, TaskUpdateById) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task "update-by-id" 0  )";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::UPDATE);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::ID);
    EXPECT_EQ(request->task->getId(), 0);
}


TEST(ParserTest, TaskUpdateByName) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task update-by-name '  old task '  )";
    parser->parse(command, request, parseError);

    EXPECT_EQ(request->mode, requestMode::UPDATE);
    EXPECT_EQ(request->code, requestCode::TASK);
    EXPECT_EQ(request->findBy, requestFindBy::NAME);
    EXPECT_EQ(request->task->getName(), "old task");
}


// ---- Parse task invalid command test ---- //

TEST(ParserTest, TaskGetByIdBadId) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(task get-by-id "first task")";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid ID");
}

TEST(ParserTest, TaskGetByIdBadCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(task  get-by-id 1 2)";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

TEST(ParserTest, TaskGetByNameBadCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(task get-by-name first task )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

TEST(ParserTest, TaskSaveBadCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(  task new "first task" )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

TEST(ParserTest, TaskDeleteByIdBadId) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"(  task delete-by-id "bad task " )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid ID");
}

TEST(ParserTest, TaskDeleteByNameBadCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task delete-by-name bad task  )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}

TEST(ParserTest, TaskUpdateByIdBadId) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task update-by-id o  )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid ID");
}


TEST(ParserTest, TaskUpdateByNameBadCommand) {
    auto parser = std::make_unique<Parser>();
    auto request = std::make_shared<Request>();
    auto parseError = std::make_shared<ParseError>();
    std::string command = R"( task update-by-name '  old task ' del )";
    parser->parse(command, request, parseError);

    EXPECT_TRUE(parseError->isError);
    EXPECT_EQ(parseError->errorBody, "invalid command");
}


