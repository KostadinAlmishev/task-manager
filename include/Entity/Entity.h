//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_ENTITY_H
#define TASK_MANAGER_ENTITY_H


#include <string>

class Entity {
protected:
    unsigned long int id;
    std::string name="";
    std::string description = "";
public:
    std::string GetName(){ return name;}
    std::string GetDescripton(){ return  description;}
    virtual  std::string GetStatus()= 0;
    unsigned long int GetId(){ return  id;}

};


#endif //TASK_MANAGER_ENTITY_H
