//
// Created by daniil on 04.12.2019.
//

#ifndef TASK_MANAGER_VALIDRESPONSE_H
#define TASK_MANAGER_VALIDRESPONSE_H

#include <string>
#include "entities/Entity.h"


struct validResponse{
    bool Valid ;
    Entity& entity;
    std::string request;
    std::string ResponseERROR;
    validResponse( Entity &ent ): entity(ent) {;}
};

#endif //TASK_MANAGER_VALIDRESPONSE_H
