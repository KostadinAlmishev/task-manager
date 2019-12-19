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

    void saveOrUpdateProject(Project);
    std::vector<Project> findAllProjects();
    Project findById(long id);
    void deleteProjectById(long id);

    bool addUser(std::shared_ptr<User> user);
    std::shared_ptr<User> getUserByName(std::string name);
    bool updateUserByName(std::shared_ptr<User>, std::string name);
    bool deleteUserByName(std::string name);

    bool addTask(std::shared_ptr<Task> task);
    std::shared_ptr<Task> getTaskById(long id);
    bool updateTaskById(std::shared_ptr<Task>, long id);
    bool deleteTaskById(long id);
};


#endif //TASK_MANAGER_COMMANDMANAGER_H
