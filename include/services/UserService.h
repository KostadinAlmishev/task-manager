//
// Created by daniil on 04.12.2019.
//

#ifndef TASK_MANAGER_USERSERVICE_H
#define TASK_MANAGER_USERSERVICE_H

#include <iostream>
#include <set>
#include "entities/Entity.h"
#include "validResponse.h"
#include "validator/IValidator.h"
#include "entities/User.h"

class UserService{
private:
    PasswordEncoder passwordEncoder;
    class UserFunctor{
    public:
        bool operator()( User left,  User right){
            return left.getName() < right.getName();
        }
    };
    std::set<User, UserFunctor > loginUsers;
    Validator validator;

public:
     validResponse Login(Entity & usr, std::string password);
     validResponse Logout(Entity & usr);

     const std::set<User,   UserFunctor> & GetLoggedIn();
     validResponse CheckPriveleges(User &usr, std::string command);
     validResponse ChangePassword(User & usr, std::string currentPassword, std::string newPassword );
     validResponse SetNewUserPassword(User& usr, std::string password);

};





#endif //TASK_MANAGER_USERSERVICE_H::ve
