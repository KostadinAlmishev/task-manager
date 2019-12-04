//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_IVALIDATOR_H
#define TASK_MANAGER_IVALIDATOR_H

#include "PasswordEncoder.h"
#include "Entity/Entity.h"
class IValidator{
private:
    PasswordEncoder *passwordEncoder = new PasswordEncoder();
public:
    virtual  Entity* CheckValidation(std::string login, std::string password ) = 0 ;
};


class Validator: public  IValidator{
public:

    //return NULL if not found
    virtual Entity* CheckValidation(std::string login, std::string password);
};
#endif //TASK_MANAGER_IVALIDATOR_H
