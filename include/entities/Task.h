//
// Created by kotik on 07.12.2019.
//

#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H

#include "Entity.h"

class Task : public Entity {
private:
    long creatorId;
    long projectId;
    std::string name;
    std::string description;
public:
    Task() : creatorId(-1), projectId(-1) {}
    void setCreatorId(long creatorId);
    long getCreatorId() const;
    void setProjectId(long projectId);
    long getProjectId() const;
    void setName(std::string name);
    std::string getName() const;
    void setDescription(std::string description);
    std::string getDescription() const;
};

#endif //TASK_MANAGER_TASK_H
