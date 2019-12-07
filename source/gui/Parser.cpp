//
// Created by kotik on 25.11.2019.
//

#include "gui/Parser.h"
#include "entities/Request.h"


void Parser::clearStartSpaces(std::string &command) const {
    auto it = command.begin();
    while (*it == ' ') it++;
    command.replace(command.begin(), it, "");
}

void Parser::clearEndSpaces(std::string &command) const {
    auto it = command.end() - 1;
    while (*it == ' ') it--;
    it++;
    command.replace(it, command.end(), "");
}

std::string Parser::getWordByPos(const std::string &command, int pos) const {
    std::string com = command;
    clearStartSpaces(com);
    std::string firstWord;
    auto it = com.begin();

    for (int i = 0; i < pos; i++) {
        while (it != com.end() && *it != ' ') it++;
        com.replace(com.begin(), com.end(), it, com.end());
        clearStartSpaces(com);
        it = com.begin();
    }

    while (it != com.end() && *it != ' ' ) {
        firstWord.push_back(*it);
        it++;
    }
    return firstWord;
}


void Parser::parseProject(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {

}
void Parser::parseTask(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string second = getWordByPos(command, 1);
    std::string third = getWordByPos(command, 2);
    request->task = std::make_shared<Task>();
    request->code = requestCode::TASK;

    if (second == "get-by-id" && !third.empty()) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "new" && third.empty()) {
        request->mode = requestMode::SAVE;
    }
    else if (second == "delete-by-id" && !third.empty()) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "update-by-id" && !third.empty()) {
        try {
            request->task->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::UPDADE;
        request->findBy = requestFindBy::ID;
    }
    else {
        parseError->isError = true;
        parseError->errorBody = "invalid command";
    }
}
void Parser::parseUser(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string second = getWordByPos(command, 1);
    std::string third = getWordByPos(command, 2);
    request->user = std::make_shared<User>();
    request->code = requestCode::USER;

    if (second == "get-by-id" && !third.empty()) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "get-by-name" && !third.empty()) {
        request->user->setName(third);
        request->mode = requestMode::GET;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "new" && third.empty()) {
        request->mode = requestMode::SAVE;
    }
    else if (second == "delete-by-id" && !third.empty()) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "delete-by-name" && !third.empty()) {
        request->user->setName(third);
        request->mode = requestMode::DELETE;
        request->findBy = requestFindBy::NAME;
    }
    else if (second == "update-by-id" && !third.empty()) {
        try {
            request->user->setId(std::stoi(third));
        }
        catch (const std::exception& ex) {
            parseError->isError = true;
            parseError->errorBody = "invalid id";
        }
        request->mode = requestMode::UPDADE;
        request->findBy = requestFindBy::ID;
    }
    else if (second == "update-by-name" && !third.empty()) {
        request->user->setName(third);
        request->mode = requestMode::UPDADE;
        request->findBy = requestFindBy::NAME;
    }
    else {
        parseError->isError = true;
        parseError->errorBody = "invalid command";
    }
}
void Parser::parseGroup(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {

}
void Parser::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    std::string first = getWordByPos(command, 0);
    std::string second = getWordByPos(command, 1);
    if (first == "quit") parseError->isQuit = true;
    else if (first == "project") {
//        request->code = requestCode::PROJECT;
    }
    else if (first == "task") {
        request->code = requestCode::TASK;
        parseTask(command, request, parseError);
    }
    else if (first == "user") {
        request->code = requestCode::USER;
        parseUser(command, request, parseError);
    }
    else if (first == "sign-out" && second.empty()) {
        request->mode = requestMode::DEAUTHORIZATION;
    }
    else if (first == "sign-in" && second.empty()) {
        request->user = std::make_shared<User>();
        request->mode = requestMode::AUTHORIZATION;
    }
    else {
        parseError->isError = true;
        parseError->errorBody = "invalid command";
    }
}