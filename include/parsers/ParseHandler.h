#ifndef TASKMANAGER_PARSEHANDLER_H
#define TASKMANAGER_PARSEHANDLER_H

#include <iostream>
#include <memory>
#include <vector>

#include "parsers/Parser.h"
#include "entities/Request.h"
#include "entities/Response.h"
#include "stringFunctions/StringFunctions.h"


class ParseHandler {
protected:
    std::string command;
    std::vector<std::shared_ptr<ParseHandler>> nextHandlers;
    virtual void initNextHandlers() = 0;
    virtual void checkNextHandlers(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
    virtual void checkFinished(std::string command, std::shared_ptr<ParseError> parseError, int amountOfWords);
public:
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) = 0;
    virtual std::string getHandlerCommand();
};

class BaseHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    BaseHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

// ---- Handlers for first word ---- //

class UndoHandler : public ParseHandler {
 protected:
  virtual void initNextHandlers() override;
 public:
  UndoHandler();
  virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class TaskHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    TaskHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};


class UserHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    UserHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class ProjectHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    ProjectHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class QuitHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    QuitHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class SignInHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    SignInHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class SignOutHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    SignOutHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

// ---- Delete Update New Get handlers ---- //

class GetHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    GetHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class NewHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    NewHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class DeleteHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    DeleteHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};

class UpdateHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    UpdateHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};


// ---- way to find entity ---- //

class ByNameHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    ByNameHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};


class ByIdHandler : public ParseHandler {
protected:
    virtual void initNextHandlers() override;
public:
    ByIdHandler();
    virtual void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) override;
};





#endif //TASKMANAGER_PARSEHANDLER_H

/*
if (first == "quit") parseError->isQuit = true;
else if (first == "project" && !StrFunc::isEmpty(second) ) {
// TODO add project parsing
}
else if (first == "task" && !StrFunc::isEmpty(second)) {
request->code = requestCode::TASK;
parseTask(command, request, parseError);
}
else if (first == "user" && !StrFunc::isEmpty(second)) {
request->code = requestCode::USER;
parseUser(command, request, parseError);
}
else if (first == "sign-out"  && StrFunc::isEmpty(second)) {
request->mode = requestMode::DEAUTHORIZATION;
}
else if (first == "sign-in" && StrFunc::isEmpty(second)) {
request->user = std::make_shared<User>();
request->mode = requestMode::AUTHORIZATION;
}
else {
parseError->isError = true;
parseError->errorBody = "invalid command";
}*/
