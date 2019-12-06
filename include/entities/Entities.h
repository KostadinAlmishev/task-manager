#ifndef TASK_MANAGER_ENTITIES_H
#define TASK_MANAGER_ENTITIES_H

#include <iostream>
#include <string>

#define PR(a) std::cout << #a << " = " << a << std::endl;


class Entity {
private:
    long id;
public:
    Entity() : id(-1) {}
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

#endif //TASK_MANAGER_ENTITIES_H
