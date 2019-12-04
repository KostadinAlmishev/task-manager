//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_KEYGEN_H
#define TASK_MANAGER_KEYGEN_H


#include <stdint-gcc.h>
#include "ICrypto.h"
class KeyGen {
private:
    const uint64_t p;
    const uint64_t q;
public:
    KeyGen(ICrypto&, ICrypto&);
};


#endif //TASK_MANAGER_KEYGEN_H
