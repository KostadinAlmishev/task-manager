//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_ENTITY_H
#define TASK_MANAGER_ENTITY_H


#include <iostream>
#include <string>

class Entity {
private:
    long id;
public:
    Entity() : id(-1) {}
    explicit Entity(long id);
    Entity(const Entity &) = default;

    long getId() const noexcept;
    void setId(long id) noexcept;
    virtual std::string toString() const {return "";};

    bool operator==(const Entity& rhs) const;

    virtual ~Entity() = default;
};



#endif //TASK_MANAGER_ENTITY_H
