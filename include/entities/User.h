//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_USER_H
#define TASK_MANAGER_USER_H


#include "Entity.h"


class User : public Entity {
private:
    std::string name="";
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


    bool operator==(const User& right){return this->getName() == right.getName();}
};
#endif //TASK_MANAGER_USER_H
