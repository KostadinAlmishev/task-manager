//
// Created by kotik on 25.11.2019.
//

#include "gui/Parser.h"
#include "entities/Request.h"

void Parser::parseProject(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {

}
void Parser::parseTask(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string second = StrFunc::getWordByPos(command, 1);
    std::string third = StrFunc::getWordByPos(command, 2);
    std::string fourth = StrFunc::getWordByPos(command, 3);
    request->task = std::make_shared<Task>();
    request->code = requestCode::TASK;

    if (second == "get-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "get-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->task->setName(third);
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "new" && StrFunc::isEmpty(third)) {
        request->mode = requestMode::SAVE;
    }
    else if (second == "delete-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "delete-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->task->setName(third);
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "update-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::UPDATE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "update-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->task->setName(third);
        request->mode = requestMode::UPDATE;
        request->findBy = requestFindBy::NAME;
    }
    else {
        parseError->isError = true;
        parseError->errorBody = "invalid command";
    }
}
void Parser::parseUser(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string second = StrFunc::getWordByPos(command, 1);
    std::string third = StrFunc::getWordByPos(command, 2);
    std::string fourth = StrFunc::getWordByPos(command, 3);
    request->user = std::make_shared<User>();
    request->code = requestCode::USER;

    if (second == "get-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "get-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->user->setName(third);
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "new" && StrFunc::isEmpty(third)) {
        request->mode = requestMode::SAVE;
    }
    else if (second == "delete-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "delete-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {

    }
    else if (second == "delete-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->user->setName(third);
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "update-by-id" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid ID";
        }
        request->mode = requestMode::UPDATE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "update-by-name" && !StrFunc::isEmpty(third) && StrFunc::isEmpty(fourth)) {
        request->user->setName(third);
        request->mode = requestMode::UPDATE;
        request->findBy = requestFindBy::NAME;
    }
    else {
        parseError->isError = true;
        parseError->errorBody = "invalid command";
    }
}
void Parser::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string first = StrFunc::getWordByPos(command, 0);
    std::string second = StrFunc::getWordByPos(command, 1);
    if (first == "quit") parseError->isQuit = true;
    else if (first == "project" && !StrFunc::isEmpty(second) ) {
//        request->code = requestCode::PROJECT;
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
    }
}