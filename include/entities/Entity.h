#ifndef TASK_MANAGER_ENTITY_H
#define TASK_MANAGER_ENTITY_H

#include <iostream>
#include <string>



class Entity {
private:
    long id;
public:
    Entity() : id(-1) {}
    long getId() const;
    void setId(long id);
};










#endif //TASK_MANAGER_ENTITY_H
