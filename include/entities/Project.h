//
// Created by kotik on 07.12.2019.
//

#ifndef TASK_MANAGER_PROJECT_H
#define TASK_MANAGER_PROJECT_H

#include "Entity.h"
#include "Project.h"
#include "Task.h"
#include "User.h"


class Project : public Entity {
private:
    std::string name;
    std::string description;
public:
    std::string getName() const;
    std::string getDescription() const;
    void setName(std::string name);
    void setDescription(std::string description);
};


#endif //TASK_MANAGER_PROJECT_H

