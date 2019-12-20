#ifndef TASK_MANAGER_COMMANDMANAGER_H
#define TASK_MANAGER_COMMANDMANAGER_H



#include <iostream>
#include <memory>
#include <vector>

#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"



class CommandManager {
private:
    std::vector<std::shared_ptr<Task>> tasks;
    std::vector<std::shared_ptr<User>> users;
public:
    CommandManager();

    bool addProject(std::shared_ptr<Task> task);
    std::shared_ptr<Task> getProjectById(int id);
    bool updateProjectById(std::shared_ptr<Task> task, int id);
    bool deleteProjectById(int id);

    bool addUser(std::shared_ptr<User> user);
    std::shared_ptr<User> getUserByName(std::string name);
    std::shared_ptr<User> getUserById(int id);
    bool updateUserByName(std::shared_ptr<User> user, std::string name);
    bool deleteUserByName(std::string name);
    bool deleteUserById(int id);

    bool addTask(std::shared_ptr<Task> task);
    std::shared_ptr<Task> getTaskById(int id);
    bool updateTaskById(std::shared_ptr<Task> task, int id);
    bool deleteTaskById(int id);
};


#endif //TASK_MANAGER_COMMANDMANAGER_H
