//
// Created by daniil on 11.11.2019.
//

#ifndef TASK_MANAGER_ENCRYPTOR_H
#define TASK_MANAGER_ENCRYPTOR_H


#include "ICrypto.h"

class Encryptor: public ICrypto {
public:
    virtual Key GetPublicKey(){
        return publicKey;
    }
    virtual std::string Execute(std::string input);
};


#endif //TASK_MANAGER_ENCRYPTOR_H
