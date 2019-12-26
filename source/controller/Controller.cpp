#include <memory>

#include "controller/CommandManager.h"
#include "controller/Controller.h"
#include "entities/Entity.h"
#include "tracking/Email.h"

const int ID_NOT_FOUNDED_ENTITY = -1;

Controller::Controller() {
  std::string host = "smtp.yandex.ru";
  unsigned int port = 465;
  std::string login = "";
  std::string password = "";
  std::shared_ptr<Subscriber> email = std::make_shared<Email<CurlCallbacks>>(host, port, login, password);
  commandManager = std::make_shared<CommandManager>("../resources/dbProperties.txt");
  commandManager->addSubscriber(email);
  securityManager = std::make_shared<SecurityManager>();
}

void Controller::checkRequest(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  checkPrivelegies(request, response);
  switch (request->mode) {
    case requestMode::GET:response->mode = responseMode::PRINT;
      getEntity(request, response);
      break;
    case requestMode::NEW:addEntity(request, response);
      break;
    case requestMode::DELETE:deleteEntity(request, response);
      break;
    case requestMode::UPDATE:updateEntity(request, response);
      break;
    case requestMode::AUTHORIZATION:Authorization(request, response);
      break;
    case requestMode::DEAUTHORIZATION:Deauthorization(request, response);
      break;
    case requestMode::UNDO:commandManager->undo(request->currentUser->getName());
      break;
  }
}

void Controller::getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  switch (request->code) {
    case requestCode::USER:
      switch (request->findBy) {
        case requestFindBy::ID: {
          auto user = commandManager->getUserById(request->fbId);
          if (user->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->user = std::dynamic_pointer_cast<User>(user);
            response->code = responseCode::USER;
          } else {
            response->isError = true;
            response->errorBody = "there is no user with such name";
          }
          break;
        }
        case requestFindBy::NAME:auto user = commandManager->getUserByName(request->fbName);
          if (user->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->user = std::dynamic_pointer_cast<User>(user);
            response->code = responseCode::USER;
          } else {
            response->isError = true;
            response->errorBody = "there is no user with such name";
          }
          break;
      }
      break;

    case requestCode::TASK:
      switch (request->findBy) {
        case requestFindBy::ID: {
          auto task = commandManager->getTaskById(request->fbId);
          if (task->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->task = std::dynamic_pointer_cast<Task>(task);
            response->code = responseCode::TASK;
          } else {
            response->isError = true;
            response->errorBody = "there is no task with such ID";
          }
          break;
        }
        case requestFindBy::NAME: {
          auto task = commandManager->getTaskByName(request->fbName);
          if (task->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->task = std::dynamic_pointer_cast<Task>(task);
            response->code = responseCode::TASK;
          } else {
            response->isError = true;
            response->errorBody = "there is no task with such name";
          }
          break;
        }
      }
      break;

    case requestCode::PROJECT:
      switch (request->findBy) {
        case requestFindBy::ID: {
          auto project = commandManager->getProjectById(request->fbId);
          if (project->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->project = std::dynamic_pointer_cast<Project>(project);
            response->code = responseCode::PROJECT;
          } else {
            response->isError = true;
            response->errorBody = "there is no project with such ID";
          }
          break;
        }
        case requestFindBy::NAME: {
          auto project = commandManager->getProjectByName(request->fbName);
          if (project->getId() != ID_NOT_FOUNDED_ENTITY) {
            response->project = std::dynamic_pointer_cast<Project>(project);
            response->code = responseCode::PROJECT;
          } else {
            response->isError = true;
            response->errorBody = "there is no project with such name";
          }
          break;
        }
      }
      break;
  }

}

void Controller::addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  switch (request->code) {
    case requestCode::USER: {
      try {
        commandManager->addUser(request->currentUser, request->user);
      } catch (...) {
        response->isError = true;
        response->errorBody = "error while adding user";
      }
      break;
    }
    case requestCode::TASK: {
      try {
        commandManager->addTask(request->currentUser, request->task);
      } catch (...) {
        response->isError = true;
        response->errorBody = "error while adding task";
      }
      break;
    }
    case requestCode::PROJECT: {
      try {
        commandManager->addProject(request->currentUser, request->project);
      } catch (...) {
        response->isError = true;
        response->errorBody = "error while adding project";
      }
      break;
    }
  }
}

void Controller::updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  switch (request->code) {
    case requestCode::USER:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<User> user = std::dynamic_pointer_cast<User>(commandManager->getUserByName(request->fbName));
          if (user->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such user";
          }

          request->user->setId(user->getId());
          if (request->user->getName().empty())
            request->user->setName(user->getName());
          if (request->user->getPassword().empty())
            request->user->setPassword(user->getPassword());
          if (request->user->getEmail().empty())
            request->user->setEmail(user->getEmail());

          try {
            commandManager->updateUser(request->currentUser, request->user);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while updating task";
          }
          break;
        }
      }
      break;

    case requestCode::TASK:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<Task> task = std::dynamic_pointer_cast<Task>(commandManager->getTaskByName(request->fbName));
          if (task->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such task";
          }

          request->task->setId(task->getId());
          request->task->setCreatorId(task->getCreatorId());
          request->task->setProjectId(task->getProjectId());
          if (request->task->getName().empty())
            request->task->setName(task->getName());
          if (request->task->getDescription().empty())
            request->task->setDescription(task->getDescription());

          try {
            commandManager->updateTask(request->currentUser, request->task);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while updating task";
          }
          break;
        }
      }
      break;

    case requestCode::PROJECT:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<Project> project = std::dynamic_pointer_cast<Project>(commandManager->getProjectByName(request->fbName));
          if (project->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such project";
          }

          request->project->setId(project->getId());
          if (request->project->getName().empty())
            request->project->setName(project->getName());
          if (request->project->getDescription().empty())
            request->project->setDescription(project->getDescription());

          try {
            commandManager->updateProject(request->currentUser, request->project);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while deleting project";
          }
          break;
        }
      }
      break;
  }
}

void Controller::deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  switch (request->code) {
    case requestCode::USER:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<Entity> user = commandManager->getUserByName(request->fbName);
          if (user->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such user";
          }
          try {
            commandManager->deleteUser(request->currentUser, user);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while deleting task";
          }
          break;
        }
      }
      break;

    case requestCode::TASK:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<Entity> task = commandManager->getTaskByName(request->fbName);
          if (task->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such task";
          }
          try {
            commandManager->deleteTask(request->currentUser, task);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while deleting task";
          }
          break;
        }
      }
      break;

    case requestCode::PROJECT:
      switch (request->findBy) {
        case requestFindBy::NAME: {
          std::shared_ptr<Entity> project = commandManager->getProjectByName(request->fbName);
          if (project->getId() == ID_NOT_FOUNDED_ENTITY) {
            response->isError = true;
            response->errorBody = "there is no such project";
          }
          try {
            commandManager->deleteProject(request->currentUser, project);
          } catch (...) {
            response->isError = true;
            response->errorBody = "error while deleting project";
          }
          break;
        }
      }
      break;
  }
}

void Controller::Authorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  std::string userName = request->user->getName();
  std::string userPas = request->user->getPassword();
  std::shared_ptr<User> userFromDB = std::dynamic_pointer_cast<User>(commandManager->getUserByName(userName));
  if (userFromDB->getId() != ID_NOT_FOUNDED_ENTITY) {
    securityManager->login(userFromDB, userPas, response);
    if (!response->isError)
      response->mode = responseMode::SUCCESSFULL_AUTHORIZATION;
      response->user = userFromDB;
  } else {
    response->isError = true;
    response->errorBody = "There is no user with such password or name";
  }
}

void Controller::Deauthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  response->mode = responseMode::SUCCESSFULL_DEAUTHORIZATION;
}

void Controller::checkPrivelegies(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {}

void Controller::checkAuthorized(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
  securityManager->isUserAuthorized(request->user);
}

