//
// Created by kotik on 03.12.2019.
//

#ifndef TASK_MANAGER_TASKMANAGER_H
#define TASK_MANAGER_TASKMANAGER_H

#include "Entities.h"
#include <vector>
#include <memory>


class TaskManager {
private:

public:
    void saveOrUpdateProject(Project);
    std::vector<Project> findAllProjects();
    Project findById(long id);
    void deleteProjectById(long id);
    void saveUser();
    void addTask(Task task);
    std::unique_ptr<Task> findTaskById(long id);
    void update(Task task);
};








#endif //TASK_MANAGER_TASKMANAGER_H
