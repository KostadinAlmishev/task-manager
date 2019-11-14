//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_ICRYPTO_H
#define TASK_MANAGER_ICRYPTO_H

#include "Key.h"
#include <iostream>
#include <string>

//decrypt  encrypt interface
class ICrypto {
protected:
    Key publicKey;
    Key privateKey;
public:
    virtual Key GetPublicKey() = 0;
    virtual std::string Execute(std::string) = 0;
friend class KeyGen;
};


#endif //TASK_MANAGER_ICRYPTO_H
