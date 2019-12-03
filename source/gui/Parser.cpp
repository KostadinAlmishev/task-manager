//
// Created by kotik on 25.11.2019.
//

#include "Parser.h"


void Parser::clearStartSpaces(std::string &command) const {
    auto it = command.begin();
    while (*it == ' ') it++;
    command.replace(command.begin(), it, "");
}

std::string Parser::getFirstWord(const std::string &command) const {
    std::string com = command;
    clearStartSpaces(com);
    std::string firstWord;
    auto it = com.begin();
    while (it != com.end() && *it != ' ' ) {
        firstWord.push_back(*it);
        it++;
    }
    return firstWord;
}


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
    std::cout << "|" << getFirstWord(command) << "|" << std::endl;
    if (getFirstWord(command) == "quit") ec->isQuit = true;
    std::cout << command << " parsed" << std::endl;
    return ec;
}