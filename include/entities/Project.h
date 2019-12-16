//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_PROJECT_H
#define TASK_MANAGER_PROJECT_H


#include "Entity.h"


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
