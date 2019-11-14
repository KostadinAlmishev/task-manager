//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_DECRYPTOR_H
#define TASK_MANAGER_DECRYPTOR_H

#include "ICrypto.h"

class Decryptor : public ICrypto  {
public:
    virtual std::string Execute(std::string );
    virtual Key GetPublicKey(){
        return publicKey;
    }
};


#endif //TASK_MANAGER_DECRYPTOR_H
