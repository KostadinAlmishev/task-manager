//
// Created by kotik on 03.12.2019.
//

#include "TaskManager.h"
#include "Entities.h"
#include <memory>

std::unique_ptr<Task> TaskManager::findTaskById(long id) {
    std::unique_ptr<Task> task;
    task->setId(1);
    task->setCreatorId(1);
    task->setDescription("Here is some information about task with id 1");
    task->setName("First task");
    task->setProjectId(1);
    return task;
}