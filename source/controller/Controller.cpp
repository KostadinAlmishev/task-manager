#include <memory>


#include "controller/CommandManager.h"
#include "controller/Controller.h"
#include "entities/Entity.h"

#define PR(a) std::cout << #a << " = " << a << std::endl;

const int ID_NOT_FOUNDED_ENTITY = -1;

Controller::Controller() {
    commandManager = std::make_shared<CommandManager>();
    securityManager = std::make_shared<SecurityManager>();
}






void Controller::checkRequest(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {

    checkPrivelegies(request, response);
    switch (request->mode) {
        case requestMode::GET:
            response->mode = responseMode::PRINT;
            getEntity(request, response);
            break;
        case requestMode::NEW:
            addEntity(request, response);
            break;
        case requestMode::DELETE:
            deleteEntity(request, response);
            break;
        case requestMode::UPDATE:
            updateEntity(request, response);
            break;
        case requestMode::AUTHORIZATION:
            Authorization(request, response);
            break;
        case requestMode::DEAUTHORIZATION:
            Deauthorization(request, response);
            break;
    }
}



void Controller::getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch(request->code) {
        case requestCode::USER:
            switch (request->findBy) {
                case requestFindBy::ID:{

                    break;
                }
                case requestFindBy::NAME:
                    auto user = commandManager->getUserByName(request->fbName);
                    if (user->getId() != ID_NOT_FOUNDED_ENTITY) {
                        response->user = user;
                        response->code = responseCode::USER;
                    }
                    else {
                        response->isError = true;
                        response->errorBody = "there is no use with such name";
                    }
                    break;
            }
            break;

        case requestCode::TASK:
            switch (request->findBy) {
                case requestFindBy::ID:{
                    auto task = commandManager->getTaskById(request->fbId);
                    if (task->getId() != ID_NOT_FOUNDED_ENTITY) {
                        response->task = task;
                        response->code = responseCode::TASK;
                    }
                    else {
                        response->isError = true;
                        response->errorBody = "there is no task with such ID";
                    }
                    break;
                }
                case requestFindBy::NAME:
                    auto task = commandManager->getTaskById(request->fbId);
                    if (task->getId() != ID_NOT_FOUNDED_ENTITY) {
                        response->task = task;
                        response->code = responseCode::TASK;
                    }
                    else {
                        response->isError = true;
                        response->errorBody = "there is no task with such name";
                    }
                    break;
            }
            break;


        case requestCode::PROJECT:

            break;
    }

}

void Controller::addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch(request->code) {
        case requestCode::USER:
            if (commandManager->addUser(request->user)) {}
            else {
                response->isError = true;
                response->errorBody = "error while adding user";
            }
            break;

        case requestCode::TASK:
            if (commandManager->addTask(request->task)) {}
            else {
                response->isError = true;
                response->errorBody = "error while adding task";
            }
            break;

        case requestCode::PROJECT:

            break;
    }
}

void Controller::updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch(request->code) {
        case requestCode::USER:
            switch (request->findBy) {
                case requestFindBy::ID:{

                    break;
                }
                case requestFindBy::NAME:
                    if (commandManager->updateUserByName(request->user, request->fbName)) {}
                    else {
                        response->isError = true;
                        response->errorBody = "there is no such name";
                    }
                    break;
            }
            break;


        case requestCode::TASK:
            switch (request->findBy) {
                case requestFindBy::ID:{
                    if (commandManager->updateTaskById(request->task, request->fbId)) {}
                    else {
                        response->isError = true;
                        response->errorBody = "there is no such id";
                    }
                    break;
                }
                case requestFindBy::NAME:

                    break;
            }
            break;


        case requestCode::PROJECT:

            break;
    }
}

void Controller::deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch(request->code) {
        case requestCode::USER:
            switch (request->findBy) {
                case requestFindBy::ID:{

                    break;
                }
                case requestFindBy::NAME:
                    if(commandManager->deleteUserByName(request->fbName)) {}
                    else {
                        response->isError = true;
                        response->errorBody = "there is no such name";
                    }
                    break;
            }
            break;


        case requestCode::TASK:
            switch (request->findBy) {
                case requestFindBy::ID:{
                    if(commandManager->deleteTaskById(request->fbId)) {}
                    else {
                        response->isError = true;
                        response->errorBody = "there is no such id";
                    }
                    break;
                }
                case requestFindBy::NAME:

                    break;
            }
            break;


        case requestCode::PROJECT:

            break;
    }
}

void Controller::Authorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    std::string userName = request->user->getName();
    std::string userPas = request->user->getPassword();
    std::shared_ptr<User> userFromDB = commandManager->getUserByName(userName);
    if (userFromDB->getId() != ID_NOT_FOUNDED_ENTITY) {
        securityManager->login(userFromDB, userPas, response);
        if (!response->isError) response->mode = responseMode::SUCCESSFULL_AUTHORIZATION;
    }
    else {
        response->isError = true;
        response->errorBody = "There is no user with such password or name";
    }
}

void Controller::Deauthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    response->mode = responseMode::SUCCESSFULL_DEAUTHORIZATION;
}

void Controller::checkPrivelegies(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {

}

void Controller::checkAuthorized(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    securityManager->isUserAuthorized(request->user);
}

