#include "parsers/ParseHandler.h"

void ParseHandler::checkNextHandlers(std::string command,
                                     std::shared_ptr<Request> request,
                                     std::shared_ptr<ParseError> parseError) {
  std::string first = StrFunc::getWordByPos(command, 0);
  bool isHandlerFound = false;
  for (auto handler : nextHandlers) {
    if (handler->getHandlerCommand() == first) {
      StrFunc::deleteFirstWord(command);
      if (!(request->commandName.empty())) request->commandName += " ";
      request->commandName += first;
      handler->parse(command, request, parseError);
      isHandlerFound = true;
      break;
    }
  }
  if (!isHandlerFound) {
    parseError->isError = true;
    parseError->errorBody = "invalid command";
  }
}
std::string ParseHandler::getHandlerCommand() {
  return command;
}

void ParseHandler::checkFinished(std::string command, std::shared_ptr<ParseError> parseError, int amountOfWords) {
  for (int i = 0; i < amountOfWords; i++) {
    StrFunc::deleteFirstWord(command);
  }
  if (!StrFunc::isEmpty(command)) {
    parseError->isError = true;
    parseError->errorBody = "invalid command";
  }
}

void BaseHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<UndoHandler>());
  nextHandlers.push_back(std::make_shared<TaskHandler>());
  nextHandlers.push_back(std::make_shared<UserHandler>());
  nextHandlers.push_back(std::make_shared<ProjectHandler>());
  nextHandlers.push_back(std::make_shared<SignInHandler>());
  nextHandlers.push_back(std::make_shared<SignOutHandler>());
  nextHandlers.push_back(std::make_shared<QuitHandler>());
}
BaseHandler::BaseHandler() {
  command = "base";
}
void BaseHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}


// ---- Handlers for first word ---- //

void QuitHandler::initNextHandlers() {}
QuitHandler::QuitHandler() {
  command = "quit";
}
void QuitHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  parseError->quitBody = "";
  parseError->isQuit = true;
  checkFinished(command, parseError, 0);
}

void SignInHandler::initNextHandlers() {}
SignInHandler::SignInHandler() {
  command = "sign-in";
}
void
SignInHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->user = std::make_shared<User>();
  request->mode = requestMode::AUTHORIZATION;
  checkFinished(command, parseError, 0);
}

void SignOutHandler::initNextHandlers() {}
SignOutHandler::SignOutHandler() {
  command = "sign-out";
}
void
SignOutHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::DEAUTHORIZATION;
  checkFinished(command, parseError, 0);
}

void TaskHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<GetHandler>());
  nextHandlers.push_back(std::make_shared<NewHandler>());
  nextHandlers.push_back(std::make_shared<UpdateHandler>());
  nextHandlers.push_back(std::make_shared<DeleteHandler>());
}
TaskHandler::TaskHandler() {
  command = "task";
}
void TaskHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {

  request->task = std::make_shared<Task>();
  request->code = requestCode::TASK;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}

void UserHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<GetHandler>());
  nextHandlers.push_back(std::make_shared<NewHandler>());
  nextHandlers.push_back(std::make_shared<UpdateHandler>());
  nextHandlers.push_back(std::make_shared<DeleteHandler>());
}
UserHandler::UserHandler() {
  command = "user";
}
void UserHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->user = std::make_shared<User>();
  request->code = requestCode::USER;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}

void ProjectHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<GetHandler>());
  nextHandlers.push_back(std::make_shared<NewHandler>());
  nextHandlers.push_back(std::make_shared<UpdateHandler>());
  nextHandlers.push_back(std::make_shared<DeleteHandler>());
}
ProjectHandler::ProjectHandler() {
  command = "project";
}
void
ProjectHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->project = std::make_shared<Project>();
  request->code = requestCode::PROJECT;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}

// ---- Delete Update New Get handlers ---- //

void GetHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<ByNameHandler>());
  nextHandlers.push_back(std::make_shared<ByIdHandler>());
}
GetHandler::GetHandler() {
  command = "get";
}
void GetHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::GET;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}

void NewHandler::initNextHandlers() {}
NewHandler::NewHandler() {
  command = "new";
}
void NewHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::NEW;
  checkFinished(command, parseError, 0);
}

void DeleteHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<ByNameHandler>());
  nextHandlers.push_back(std::make_shared<ByIdHandler>());
}
DeleteHandler::DeleteHandler() {
  command = "delete";
}
void DeleteHandler::parse(std::string command,
                          std::shared_ptr<Request> request,
                          std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::DELETE;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}

void UpdateHandler::initNextHandlers() {
  nextHandlers.push_back(std::make_shared<ByNameHandler>());
  nextHandlers.push_back(std::make_shared<ByIdHandler>());
}
UpdateHandler::UpdateHandler() {
  command = "update";
}
void UpdateHandler::parse(std::string command,
                          std::shared_ptr<Request> request,
                          std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::UPDATE;
  initNextHandlers();
  checkNextHandlers(command, request, parseError);
}



// ---- way to find entity ---- //

void ByNameHandler::initNextHandlers() {}
ByNameHandler::ByNameHandler() {
  command = "by-name";
}
void
ByNameHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  std::string first = StrFunc::getWordByPos(command, 0);
  checkFinished(command, parseError, 1);
  request->fbName = first;
  request->findBy = requestFindBy::NAME;
}

void ByIdHandler::initNextHandlers() {}
ByIdHandler::ByIdHandler() {
  command = "by-id";
}

void ByIdHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  std::string first = StrFunc::getWordByPos(command, 0);
  try {
    request->fbId = std::stoi(first);
    checkFinished(command, parseError, 1);
    request->findBy = requestFindBy::ID;
  }
  catch (const std::exception &ex) {
    parseError->isError = true;
    parseError->errorBody = "invalid ID";
  }
}


void UndoHandler::initNextHandlers() {}
UndoHandler::UndoHandler() {
  command="undo";
}
void UndoHandler::parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError) {
  request->mode = requestMode::UNDO;
}

