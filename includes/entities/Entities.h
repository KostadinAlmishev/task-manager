//
// Created by kotik on 24.11.2019.
//

#ifndef TASK_MANAGER_ENTITIES_H
#define TASK_MANAGER_ENTITIES_H

#include <iostream>
#include <string>

class Entity {
private:
    long id;
public:
    long getId() const;
    void setId(long id);
};



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


class User : public Entity {
private:
    std::string name;
    std::string password;
    std::string email;
public:
    void setName(std::string name);
    std::string getName() const;
    void setPassword(std::string password);
    std::string getPassword() const;
    void setEmail(std::string email);
    std::string getEmail() const;
};
class Task : public Entity {
private:
    long creatorId;
    long projectId;
    std::string name;
    std::string description;
public:
    void setCreatorId(long creatorId);
    long getCreatorId() const;
    void setProjectId(long projectId);
    long getProjectId() const;
    void setName(std::string name);
    std::string getName() const;
    void setDescription(std::string description);
    std::string getDescription() const;
};

#endif //TASK_MANAGER_ENTITIES_H
