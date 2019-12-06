//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_IVALIDATOR_H
#define TASK_MANAGER_IVALIDATOR_H

#include "include/Encoder/PasswordEncoder.h"
#include "Entity/Entity.h"

class IValidator{
protected:
    PasswordEncoder passwordEncoder ;
public:
    virtual  bool CheckValidation(std::string inputPassword, std::string EncodedPassword ) = 0 ;
    virtual std::string ReinstallPassword(std::string newPassword , std::string inputPassword, std::string EncodedPassword)= 0;
};


class Validator: public  IValidator{
public:

    //returns true if valid
    bool  CheckValidation(std::string inputPassword, std::string EncodedPassword) override ;
    std::string ReinstallPassword(std::string newPassword, std::string inputPassword,
                                              std::string EncodedPassword) override;
};
#endif //TASK_MANAGER_IVALIDATOR_H
