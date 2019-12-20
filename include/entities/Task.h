#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H

#include "Entity.h"
#include "Project.h"
#include "Task.h"
#include "User.h"


class Task : public Entity {
private:
    int creatorId;
    int projectId;
    std::string name;
    std::string description;
public:
    Task() : creatorId(-1), projectId(-1) {}
    void setCreatorId(int creatorId);
    int getCreatorId() const;
    void setProjectId(int projectId);
    int getProjectId() const;
    void setName(std::string name);
    std::string getName() const;
    void setDescription(std::string description);
    std::string getDescription() const;
};

#endif //TASK_MANAGER_TASK_H
