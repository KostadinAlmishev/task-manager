//
// Created by daniil on 11.11.2019.
//

#ifndef TASK_MANAGER_KEY_H
#define TASK_MANAGER_KEY_H


#include <iostream>

class Key {
public:
    uint64_t exp;
    uint64_t mod;
    Key(uint64_t exp, uint64_t mod): exp(exp), mod(mod){;}
    Key(){;}
};


#endif //TASK_MANAGER_KEY_H
