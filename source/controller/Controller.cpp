#include "controller/Controller.h"
#include "entities/Entity.h"
#include "controller/CommandManager.h"

#include <memory>

Controller::Controller() {
    commandManager = std::make_shared<CommandManager>();
}


void Controller::checkRequest(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch (request->mode) {
        case requestMode::GET:
            response->mode = responseMode::PRINT;
            getEntity(request, response);
            break;
        case requestMode::SAVE:
            addEntity(request, response);
            break;
        case requestMode::DELETE:
            deleteEntity(request, response);
            break;
        case requestMode::UPDADE:
            updateEntity(request, response);
            break;
        case requestMode::AUTHORIZATION:
            checkAuthorization(request, response);
            break;
        case requestMode::DEAUTHORIZATION:
            checkDeauthorization(request, response);
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
                    auto user = commandManager->getUserByName(request->user->getName());
                    if (user->getId() != -1) {
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
                    auto task = commandManager->getTaskById(request->task->getId());
                    if (task->getId() != -1) {
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
                    if (commandManager->updateUserByName(request->user, request->user->getName())) {}
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
                    if (commandManager->updateTaskById(request->task, request->task->getId())) {}
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
                    if(commandManager->deleteUserByName(request->user->getName())) {}
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
                    if(commandManager->deleteTaskById(request->task->getId())) {}
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

void Controller::checkAuthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    response->mode = responseMode::SUCCESSFULL_AUTHORIZATION;
}

void Controller::checkDeauthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    response->mode = responseMode::SUCCESSFULL_DEAUTHORIZATION;
}

