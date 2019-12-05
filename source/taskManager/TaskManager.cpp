#include "TaskManager.h"
#include "Entities.h"
#include <memory>

TaskManager::TaskManager() {
    std::shared_ptr<Task> task(new Task);
    task->setId(0);
    task->setCreatorId(0);
    task->setDescription("Here is some information about task with id 0");
    task->setName("First task");
    task->setProjectId(0);

    tasks.push_back(task);

    std::shared_ptr<Task> task2(new Task);
    task2->setId(1);
    task2->setCreatorId(0);
    task2->setDescription("Yeah, some information about task with id 0");
    task2->setName("Second task");
    task2->setProjectId(0);
    tasks.push_back(task2);
}

void TaskManager::addTask(std::shared_ptr<Task> task) {
    task->setId(tasks.size());
    tasks.push_back(task);
}

std::shared_ptr<Task> TaskManager::findTaskById(long id) {
    if (id >= 0 && id < tasks.size()) {
        return tasks[id];
    }
    else {
        throw std::exception();
    }
}

void TaskManager::updateTaskById(std::shared_ptr<Task> task, long id) {
    if (id >= 0 && id < tasks.size()) {
        tasks[id] = task;
    }
    else {
        throw std::exception();
    }
}

void TaskManager::deleteTaskById(long id) {
    if (id >= 0 && id < tasks.size()) {
        tasks[id] = nullptr;
        tasks[id] = tasks[tasks.size() - 1];
        tasks[id]->setId(id);
        tasks.resize(tasks.size() - 1);
    }
    else {
        throw std::exception();
    }
}


void TaskManager::executeCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    switch (request->mode) {
        case requestMode::GET:
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
    }
}



void TaskManager::getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    if (request->findBy == requestFindBy::ID) {
        try {
            response->task = findTaskById(request->task->getId());
            response->code = responseCode::TASK;
        }
        catch (const std::exception &ex) {
            response->isError = true;
            response->errorBody = "there is no task with such ID";
        }
    }
    else if (request->findBy == requestFindBy::NAME) {

    }
}

void TaskManager::addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    try {
        addTask(request->task);
    }
    catch (const std::exception &ex) {
        response->isError = true;
        response->errorBody = "error while adding task";
    }
}

void TaskManager::updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    if (request->findBy == requestFindBy::ID) {
        try {
            updateTaskById(request->task, request->task->getId());
        }
        catch (const std::exception &ex) {
            response->isError = true;
            response->errorBody = "there is no such id";
        }
    }
    else if (request->findBy == requestFindBy::NAME) {

    }
}

void TaskManager::deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {

    try {
        deleteTaskById(request->task->getId());
    }
    catch (const std::exception &ex) {
        response->isError = true;
        response->errorBody = "there is no such id";
    }
}


