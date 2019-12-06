//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_DECRYPTOR_H
#define TASK_MANAGER_DECRYPTOR_H

#include "ICrypto.h"

class Decryptor : public ICrypto  {
public:
    std::string Execute(std::string ) override;
    Key GetPublicKey() override {
        return publicKey;
    }
    Decryptor(){;}

};


#endif //TASK_MANAGER_DECRYPTOR_H
