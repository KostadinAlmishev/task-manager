
#include "services/UserService.h"
#include "privilege/Privilege.h"


validResponse UserService::Login(Entity &usr, std::string password) {
    validResponse response(usr);
    response.request = "Login";
    response.entity = usr;
    User tmpUser= static_cast<User&>(usr);

    if(validator.CheckValidation(password, tmpUser.getPassword()) ){
        if(loginUsers.find(tmpUser)== loginUsers.end()) {
            response.Valid = true;
            loginUsers.insert(tmpUser);
        }
        else{
            response.Valid = false;
            response.ResponseERROR = "User " + tmpUser.getName()+ " already logged in";
        }
    }else{
        response.Valid = false;
        response.ResponseERROR = "validator return false";
    }
    return response;
}

validResponse UserService::ChangePassword(User &usr, std::string currentPassword, std::string newPassword) {
    validResponse response(usr);
    if(Login(usr, currentPassword).Valid){
        Logout(usr);
        usr.setPassword(passwordEncoder.Encode(newPassword));
        response.Valid = true;
    }else{
        response.Valid= false;
        response.ResponseERROR = "wrong old password";
    }
    return response;
}

const std::set<User, UserService::UserFunctor> & UserService::GetLoggedIn() {
    return loginUsers;
}

validResponse UserService::CheckPriveleges(Entity &usr, std::string command) {
    validResponse responce(usr);
    responce.request = command;

    //заглушка
    Privel
    //заглушка
    return responce;
}

validResponse UserService::Logout(Entity &usr) {

    validResponse response(usr);
    User tmpUser = static_cast<User&>(usr);
    response.request = "Logout";
    if(loginUsers.find(tmpUser) == loginUsers.end() ){
        response.Valid = false;
        response.ResponseERROR = "error at executing logout, user not logged in";
    }else{
        response.ResponseERROR = "";
        response.Valid = true;
    }

    return response;
}

validResponse UserService::SetNewUserPassword(User &usr, std::string password) {
    validResponse response(usr);
    response.request = "change password of user " + usr.getName();


    if(usr.getPassword() != "") {
        response.ResponseERROR = "not empty password";
        response.Valid = false;
    }else{
      response.Valid = true;
      usr.setPassword( passwordEncoder.Encode(password) );
    }


    return  response;
}
