#ifndef TASK_MANAGER_USER_H
#define TASK_MANAGER_USER_H

#include "Entity.h"
#include "Task.h"
#include "User.h"
#include "Project.h"


class User : public Entity {
private:
    std::string name;
    std::string password;
    std::string email;
    std::string status;
public:
    void setName(std::string name);
    std::string getName() const;
    void setPassword(std::string password);
    std::string getPassword() const;
    void setEmail(std::string email);
    std::string getEmail() const;
    void setStatus(std::string status);
    std::string getStatus() const;
};

#endif //TASK_MANAGER_USER_H
