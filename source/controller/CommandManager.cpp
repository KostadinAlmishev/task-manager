#include <memory>
#include <iostream>
#include "controller/CommandManager.h"
#include "entities/Entity.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "entities/Project.h"



CommandManager::CommandManager() {
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

    std::shared_ptr<User> user(new User);
    user->setId(0);
    user->setName("admin");
    user->setEmail("admin@mail.ru");
    user->setPassword("admin");
    user->setStatus("admin");

    users.push_back(user);

}




bool CommandManager::addTask(std::shared_ptr<Task> task) {
    task->setId(tasks.size());
    tasks.push_back(task);
    return true;
}

std::shared_ptr<Task> CommandManager::getTaskById(long id) {
    if (id >= 0 && id < tasks.size()) {
        return tasks[id];
    }
    else {
        auto invalidTask = std::make_shared<Task>();
        invalidTask->setId(-1);
        return invalidTask;
    }
}

bool CommandManager::updateTaskById(std::shared_ptr<Task> task, long id) {
    if (id >= 0 && id < tasks.size()) {
        tasks[id] = task;
        return true;
    }
    else {
        return false;
    }
}


bool CommandManager::deleteTaskById(long id) {
    if (id >= 0 && id < tasks.size()) {
        tasks[id] = nullptr;
        if (tasks[tasks.size() - 1] != nullptr) {
            tasks[id] = tasks[tasks.size() - 1];
            tasks[id]->setId(id);
        }
        tasks.resize(tasks.size() - 1);
        return true;
    }
    else {
        return false;
    }
}


bool CommandManager::addUser(std::shared_ptr<User> user) {
    user->setId(users.size());
    users.push_back(user);
    return true;
}

std::shared_ptr<User> CommandManager::getUserByName(std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getName() == name) {
            return users[i];
        }
    }
    auto invalidUser = std::make_shared<User>();
    invalidUser->setId(-1);
    return invalidUser;
}

bool CommandManager::updateUserByName(std::shared_ptr<User> user, std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getName() == name) {
            users[i] = user;
            return true;
        }
    }
    return false;
}

bool CommandManager::deleteUserByName(std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getName() == name) {
            users[i] = nullptr;
            if (users[users.size() - 1] != nullptr) {
                users[i] = users[users.size() - 1];
                users[i]->setId(i);
            }
            users.resize(users.size() - 1);
            return true;
        }
    }
    return false;
}


