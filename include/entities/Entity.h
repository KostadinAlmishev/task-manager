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
    virtual std::string toString() const = 0;

    bool operator==(const Entity& rhs) const;

    virtual ~Entity() = default;
};

#endif //TASK_MANAGER_ENTITY_H
