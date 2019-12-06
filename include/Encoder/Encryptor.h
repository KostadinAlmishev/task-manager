//
// Created by daniil on 11.11.2019.
//

#ifndef TASK_MANAGER_ENCRYPTOR_H
#define TASK_MANAGER_ENCRYPTOR_H


#include "ICrypto.h"

class Encryptor: public ICrypto {

public:
    Key GetPublicKey() override {
        return publicKey;
    }
    std::string Execute(std::string input) override ;
};


#endif //TASK_MANAGER_ENCRYPTOR_H
