#include "parser/Parser.h"
#include "entities/Request.h"



void Parser::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
    BaseHandler baseHandler;
    baseHandler.parse(command, request, parseError);
}
