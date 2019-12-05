#ifndef TASK_MANAGER_TASKMANAGER_H
#define TASK_MANAGER_TASKMANAGER_H

#include "Entities.h"
#include "Request.h"
#include "Response.h"

#include <vector>
#include <memory>



class TaskManager {
private:
    // Dummy objects
    std::vector<std::shared_ptr<Task>> tasks;
    //




public:
    TaskManager();
    void executeCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);

    void getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);

    void saveOrUpdateProject(Project);
    std::vector<Project> findAllProjects();
    Project findById(long id);
    void deleteProjectById(long id);
    void saveUser();
    void addTask(std::shared_ptr<Task> task);
    std::shared_ptr<Task> findTaskById(long id);
    void updateTaskById(std::shared_ptr<Task>, long id);
    void deleteTaskById(long id);
};




#endif //TASK_MANAGER_TASKMANAGER_H
